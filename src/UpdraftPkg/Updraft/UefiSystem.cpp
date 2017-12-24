#include "UefiSystem.hpp"

extern "C" {
#include <Library/CpuLib.h>
}

#include "Logger.hpp"

EFI_SYSTEM_TABLE *UefiSystem::SystemTable = nullptr;

EFI_GRAPHICS_OUTPUT_PROTOCOL *UefiSystem::GraphicsOutputProtocol = nullptr;

// ウォッチドッグタイマを解除
// これをやらないと起動後5分で再起動するらしい
void UefiSystem::release_watchdog_timer()
{
  const EFI_STATUS status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, nullptr);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on UEFI initialization.");
    loop_forever();
  }
}

void UefiSystem::locate_gop()
{
  const auto status =
    SystemTable->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (void **)&GraphicsOutputProtocol);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on locate EFI Graphics Output Protocol.");
    UefiSystem::loop_forever();
  }
}

void UefiSystem::check_pixel_format()
{
  const auto pixelFormat = GraphicsOutputProtocol->Mode->Info->PixelFormat;
  if(pixelFormat != PixelRedGreenBlueReserved8BitPerColor && pixelFormat != PixelBlueGreenRedReserved8BitPerColor)
  {
    Logger::Println_("Error: Not supported pixel format.");
    UefiSystem::loop_forever();
  }
}

bool UefiSystem::is_proper_graphics_mode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution)
{
  return (modeInfo->PixelFormat == PixelBlueGreenRedReserved8BitPerColor || modeInfo->PixelFormat == PixelRedGreenBlueReserved8BitPerColor) &&
    modeInfo->HorizontalResolution == horizontalResolution &&
    modeInfo->VerticalResolution == verticalResolution;
}

uint32 UefiSystem::get_proper_graphics_mode(const uint32 horizontalResolution, const uint32 verticalResolution)
{
  for(uint32 i = 0; i < GraphicsOutputProtocol->Mode->MaxMode; i++){
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo;
    uintn sizeOfModeInfo;

    const auto status = GraphicsOutputProtocol->QueryMode(GraphicsOutputProtocol, i, &sizeOfModeInfo, &modeInfo);
    if(EFI_ERROR(status))
    {
      Logger::Println_("Error: ", status, " on query video mode.");
      UefiSystem::loop_forever();
    }
    else if(is_proper_graphics_mode(modeInfo, horizontalResolution, verticalResolution))
    {
      return i;
    }
  }

  return 0;
}

void UefiSystem::set_video_mode(const uint32 mode)
{
  const auto status = GraphicsOutputProtocol->SetMode(GraphicsOutputProtocol, mode);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on set video mode.");
    UefiSystem::loop_forever();
  }
  Logger::ClearPrint();
}

void UefiSystem::initialize(EFI_SYSTEM_TABLE *ST)
{
  SystemTable = ST;

  release_watchdog_timer();

  locate_gop();

  check_pixel_format();

  set_video_mode(get_proper_graphics_mode(800, 600));
}

void UefiSystem::loop_forever()
{
  while(true) CpuSleep();
}
