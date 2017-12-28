#include "Lifecycle.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"

EFI_EVENT Lifecycle::timerEvent = nullptr;

EFI_EVENT Lifecycle::eventList[];

uintn Lifecycle::eventIndex = 0;

uint8 Lifecycle::fps = 60;

uint32 Lifecycle::frameCount = 0;

void Lifecycle::initialize()
{
  const auto status = UefiSystem::getSystemTable()->BootServices->CreateEvent(EVT_TIMER, 0, nullptr, nullptr, &timerEvent);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on timer event setup.");
    UefiSystem::sleepForever();
  }

  eventList[0] = timerEvent;
}

bool Lifecycle::update()
{
  const auto status1 = UefiSystem::getSystemTable()->BootServices->SetTimer(timerEvent, TimerRelative, 10000000 / fps);
  if(EFI_ERROR(status1))
  {
    Logger::Println_("Error: ", status1, " on update.");
    UefiSystem::sleepForever();
  }

  const auto status2 = UefiSystem::getSystemTable()->BootServices->WaitForEvent(1, eventList, &eventIndex);
  if(EFI_ERROR(status2))
  {
    Logger::Println_("Error: ", status2, " on update.");
    UefiSystem::sleepForever();
  }

  frameCount++;

  return true;
}

uint8 Lifecycle::getFPS()
{
  return fps;
}

void Lifecycle::setFPS(const uint8 _fps)
{
  fps = _fps;
}

uint32 Lifecycle::getFrameCount()
{
  return frameCount;
}
