#include "UefiSystem.hpp"

extern "C" {
#include <Library/CpuLib.h>
}

#include "Logger.hpp"

EFI_SYSTEM_TABLE *UefiSystem::s_SystemTable = nullptr;

EFI_GRAPHICS_OUTPUT_PROTOCOL *UefiSystem::s_GraphicsOutputProtocol = nullptr;

// ウォッチドッグタイマを解除
// これをやらないと起動後5分で再起動するらしい
void UefiSystem::ReleaseWatchdogTimer()
{
  const EFI_STATUS status = s_SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, nullptr);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on UEFI initialization.");
    SleepForever();
  }
}

void UefiSystem::LocateGOP()
{
  const auto status =
    s_SystemTable->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, nullptr, (void **)&s_GraphicsOutputProtocol);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on locate EFI Graphics Output Protocol.");
    SleepForever();
  }
}

void UefiSystem::CheckPixelFormat()
{
  const auto pixelFormat = s_GraphicsOutputProtocol->Mode->Info->PixelFormat;
  if(pixelFormat != PixelRedGreenBlueReserved8BitPerColor && pixelFormat != PixelBlueGreenRedReserved8BitPerColor)
  {
    Logger::Println_("Error: Not supported pixel format.");
    SleepForever();
  }
}

bool UefiSystem::IsProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution)
{
  return (modeInfo->PixelFormat == PixelBlueGreenRedReserved8BitPerColor || modeInfo->PixelFormat == PixelRedGreenBlueReserved8BitPerColor) &&
    modeInfo->HorizontalResolution == horizontalResolution &&
    modeInfo->VerticalResolution == verticalResolution;
}

uint32 UefiSystem::GetProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution)
{
  for(uint32 i = 0; i < s_GraphicsOutputProtocol->Mode->MaxMode; i++){
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo;
    uintn sizeOfModeInfo;

    const auto status = s_GraphicsOutputProtocol->QueryMode(s_GraphicsOutputProtocol, i, &sizeOfModeInfo, &modeInfo);
    if(EFI_ERROR(status))
    {
      Logger::Println_("Error: ", status, " on query video mode.");
      SleepForever();
    }
    else if(IsProperGraphicsMode(modeInfo, horizontalResolution, verticalResolution))
    {
      return i;
    }
  }

  return 0;
}

void UefiSystem::SetVideoMode(const uint32 mode)
{
  const auto status = s_GraphicsOutputProtocol->SetMode(s_GraphicsOutputProtocol, mode);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on set video mode.");
    SleepForever();
  }

  Logger::ClearPrint();
}

void UefiSystem::Initialize(EFI_SYSTEM_TABLE *SystemTable)
{
  s_SystemTable = SystemTable;

  LocateGOP();

  CheckPixelFormat();

  SetVideoMode(GetProperGraphicsMode(800, 600));

  ReleaseWatchdogTimer();
}

EFI_SYSTEM_TABLE* UefiSystem::SystemTable()
{
  return s_SystemTable;
}

EFI_GRAPHICS_OUTPUT_PROTOCOL* UefiSystem::GraphicsOutputProtocol()
{
  return s_GraphicsOutputProtocol;
}

void UefiSystem::SleepForever()
{
  while(true) ::CpuSleep();
}
