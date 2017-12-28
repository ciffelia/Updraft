#include "UefiSystem.hpp"

extern "C" {
#include <Library/CpuLib.h>
}

#include "Logger.hpp"

EFI_SYSTEM_TABLE *UefiSystem::SystemTable = nullptr;

EFI_GRAPHICS_OUTPUT_PROTOCOL *UefiSystem::GraphicsOutputProtocol = nullptr;

EFI_EVENT UefiSystem::timerEvent = nullptr;

EFI_EVENT UefiSystem::eventList[];

uintn UefiSystem::eventIndex = 0;

uint8 UefiSystem::fps = 60;

uint32 UefiSystem::frameCount = 0;

// ウォッチドッグタイマを解除
// これをやらないと起動後5分で再起動するらしい
void UefiSystem::releaseWatchdogTimer()
{
  const EFI_STATUS status = SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, nullptr);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on UEFI initialization.");
    loopForever();
  }
}

void UefiSystem::locateGOP()
{
  const auto status =
    SystemTable->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, NULL, (void **)&GraphicsOutputProtocol);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on locate EFI Graphics Output Protocol.");
    UefiSystem::loopForever();
  }
}

void UefiSystem::checkPixelFormat()
{
  const auto pixelFormat = GraphicsOutputProtocol->Mode->Info->PixelFormat;
  if(pixelFormat != PixelRedGreenBlueReserved8BitPerColor && pixelFormat != PixelBlueGreenRedReserved8BitPerColor)
  {
    Logger::Println_("Error: Not supported pixel format.");
    UefiSystem::loopForever();
  }
}

bool UefiSystem::isProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution)
{
  return (modeInfo->PixelFormat == PixelBlueGreenRedReserved8BitPerColor || modeInfo->PixelFormat == PixelRedGreenBlueReserved8BitPerColor) &&
    modeInfo->HorizontalResolution == horizontalResolution &&
    modeInfo->VerticalResolution == verticalResolution;
}

uint32 UefiSystem::getProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution)
{
  for(uint32 i = 0; i < GraphicsOutputProtocol->Mode->MaxMode; i++){
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo;
    uintn sizeOfModeInfo;

    const auto status = GraphicsOutputProtocol->QueryMode(GraphicsOutputProtocol, i, &sizeOfModeInfo, &modeInfo);
    if(EFI_ERROR(status))
    {
      Logger::Println_("Error: ", status, " on query video mode.");
      UefiSystem::loopForever();
    }
    else if(isProperGraphicsMode(modeInfo, horizontalResolution, verticalResolution))
    {
      return i;
    }
  }

  return 0;
}

void UefiSystem::setVideoMode(const uint32 mode)
{
  const auto status = GraphicsOutputProtocol->SetMode(GraphicsOutputProtocol, mode);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on set video mode.");
    UefiSystem::loopForever();
  }
  Logger::ClearPrint();
}

void UefiSystem::setupTimerEvent()
{
  const auto status = SystemTable->BootServices->CreateEvent(EVT_TIMER, 0, nullptr, nullptr, &timerEvent);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on timer event setup.");
    UefiSystem::loopForever();
  }

  eventList[0] = timerEvent;
}

void UefiSystem::initialize(EFI_SYSTEM_TABLE *ST)
{
  SystemTable = ST;

  releaseWatchdogTimer();

  locateGOP();

  checkPixelFormat();

  setVideoMode(getProperGraphicsMode(800, 600));

  setupTimerEvent();
}

bool UefiSystem::update()
{
  const auto status1 = SystemTable->BootServices->SetTimer(timerEvent, TimerRelative, 10000000 / fps);
  if(EFI_ERROR(status1))
  {
    Logger::Println_("Error: ", status1, " on update.");
    UefiSystem::loopForever();
  }

  const auto status2 = SystemTable->BootServices->WaitForEvent(1, eventList, &eventIndex);
  if(EFI_ERROR(status2))
  {
    Logger::Println_("Error: ", status2, " on update.");
    UefiSystem::loopForever();
  }

  frameCount++;

  return true;
}

void UefiSystem::loopForever()
{
  while(true) CpuSleep();
}
