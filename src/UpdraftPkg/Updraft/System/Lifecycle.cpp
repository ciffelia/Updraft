#include "Lifecycle.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Assert.hpp"

EFI_EVENT Lifecycle::s_timerEvent = nullptr;

EFI_EVENT Lifecycle::s_eventList[];

uintn Lifecycle::s_eventIndex = 0;

uint8 Lifecycle::s_fps = 60;

uint32 Lifecycle::s_frameCount = 0;

bool Lifecycle::s_isExitting = false;

void Lifecycle::CreateTimerEvent()
{
  const auto status = UefiSystem::SystemTable()->BootServices->CreateEvent(EVT_TIMER, 0, nullptr, nullptr, &s_timerEvent);
  AssertEfiStatus(status, "Failed to setup timer event.");

  s_eventList[0] = s_timerEvent;
}

void Lifecycle::SetTimer()
{
  const auto status = UefiSystem::SystemTable()->BootServices->SetTimer(s_timerEvent, ::TimerPeriodic, 10000000 / s_fps);
  AssertEfiStatus(status, "Failed to reset timer.");
}

void Lifecycle::CancelTimer()
{
  const auto status = UefiSystem::SystemTable()->BootServices->SetTimer(s_timerEvent, ::TimerCancel, 0);
  AssertEfiStatus(status, "Failed to reset timer.");
}

void Lifecycle::ResetTimer()
{
  CancelTimer();
  SetTimer();
}

void Lifecycle::WaitForTimerEvent()
{
  const auto status = UefiSystem::SystemTable()->BootServices->WaitForEvent(1, s_eventList, &s_eventIndex);
  AssertEfiStatus(status, "Failed to update.");
}

void Lifecycle::Initialize()
{
  CreateTimerEvent();

  SetTimer();
}

bool Lifecycle::Update()
{
  if (s_isExitting)
    return false;

  WaitForTimerEvent();

  s_frameCount++;

  return true;
}

void Lifecycle::Exit()
{
  s_isExitting = true;
}

uint8 Lifecycle::FPS()
{
  return s_fps;
}

void Lifecycle::FPS(const uint8 fps)
{
  s_fps = fps;
  ResetTimer();
}

uint32 Lifecycle::FrameCount()
{
  return s_frameCount;
}
