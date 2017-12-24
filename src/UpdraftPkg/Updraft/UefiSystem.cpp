#include "UefiSystem.hpp"

extern "C" {
#include <Library/CpuLib.h>
}

#include "Logger.hpp"
#include "Graphics/ColorPalette.hpp"
#include "Graphics/Screen.hpp"

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

void UefiSystem::clear_screen()
{
  Logger::ClearPrint();
  Screen::rect().draw(Palette::Black);
}

void UefiSystem::initialize(EFI_SYSTEM_TABLE *ST)
{
  SystemTable = ST;

  release_watchdog_timer();

  locate_gop();

  check_pixel_format();

  clear_screen();
}

void UefiSystem::loop_forever()
{
  while(true) CpuSleep();
}
