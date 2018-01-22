#include "Lifecycle.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Assert.hpp"

EFI_SIMPLE_TEXT_INPUT_PROTOCOL *Lifecycle::s_SimpleTextInputProtocol = nullptr;

EFI_EVENT Lifecycle::s_timerEvent = nullptr;

EFI_EVENT Lifecycle::s_eventList[];

uintn Lifecycle::s_eventIndex = 0;

uint8 Lifecycle::s_fps = 60;

uint32 Lifecycle::s_frameCount = 0;

void Lifecycle::LocateSimpleTextInputProtocol()
{
  const auto status =
      UefiSystem::SystemTable()->BootServices->LocateProtocol(&gEfiSimpleTextInProtocolGuid, nullptr, (void **)&s_SimpleTextInputProtocol);
  AssertEfiStatus(status, "Failed to locate EFI Simple Text Input Protocol.");
}

void Lifecycle::ResetInputDevice()
{
  s_SimpleTextInputProtocol->Reset(s_SimpleTextInputProtocol, false);
}

bool Lifecycle::ExitKeyPressed()
{
  EFI_INPUT_KEY key;

  const auto status = s_SimpleTextInputProtocol->ReadKeyStroke(s_SimpleTextInputProtocol, &key);
  switch (status)
  {
    case EFI_SUCCESS:
      if (key.ScanCode == SCAN_ESC)
        return true;
    case EFI_NOT_READY:
      break;
    default:
      Logger::Println_("Error: ", PrintEfiStatus(status), " on keyboard update.");
      UefiSystem::SleepForever();
  }

  return false;
}

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
  LocateSimpleTextInputProtocol();

  ResetInputDevice();

  CreateTimerEvent();

  SetTimer();
}

bool Lifecycle::Update()
{
  WaitForTimerEvent();

  s_frameCount++;

  if (ExitKeyPressed())
    return false;

  return true;
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
