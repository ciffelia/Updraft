#include "Mouse.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Assert.hpp"
#include "../Graphics/Screen.hpp"

EFI_SIMPLE_POINTER_PROTOCOL *Mouse::s_SimplePointerProtocol = nullptr;

uint64 Mouse::s_resolutionX, Mouse::s_resolutionY;

uint8 Mouse::s_mouseSpeed;

Point Mouse::s_pos, Mouse::s_delta;

bool Mouse::s_rightPressed, Mouse::s_leftPressed;

void Mouse::LocateSimplePointerProtocol()
{
  const auto status =
    UefiSystem::SystemTable()->BootServices->LocateProtocol(&gEfiSimplePointerProtocolGuid, nullptr, (void **)&s_SimplePointerProtocol);
  AssertEfiStatus(status, "Failed to locate EFI Simple Pointer Protocol.");
}

void Mouse::ResetPointerDevice()
{
  s_SimplePointerProtocol->Reset(s_SimplePointerProtocol, false);
}

void Mouse::CheckPointerDevice()
{
  const auto *mode = s_SimplePointerProtocol->Mode;
  s_resolutionX = mode->ResolutionX;
  s_resolutionY = mode->ResolutionY;

  Assert(s_resolutionX != 0 && s_resolutionY != 0 && mode->LeftButton && mode->RightButton, "The pointer device not available.");
}

void Mouse::UpdateState(const EFI_SIMPLE_POINTER_STATE *pointerState)
{
  if(pointerState == nullptr)
  {
    s_delta = {0, 0};
    return;
  }

  Point newPos;

  newPos.x = s_pos.x + (int32)((pointerState->RelativeMovementX / s_resolutionX) * s_mouseSpeed);
  newPos.y = s_pos.y + (int32)((pointerState->RelativeMovementY / s_resolutionY) * s_mouseSpeed);

  if (newPos.x < 0)
    newPos.x = 0;
  if (newPos.x >= static_cast<int32>(Screen::Width()))
    newPos.x = static_cast<int32>(Screen::Width()) - 1;
  if (newPos.y < 0)
    newPos.y = 0;
  if (newPos.y >= static_cast<int32>(Screen::Height()))
    newPos.y = static_cast<int32>(Screen::Height()) - 1;

  s_delta = newPos - s_pos;
  s_pos = newPos;

  s_leftPressed = pointerState->LeftButton == TRUE;
  s_rightPressed = pointerState->RightButton == TRUE;
}

void Mouse::Initialize()
{
  LocateSimplePointerProtocol();

  ResetPointerDevice();

  CheckPointerDevice();

  s_pos = Screen::Center();

  s_leftPressed = s_rightPressed = false;

  s_mouseSpeed = 2;
}

void Mouse::Update()
{
  EFI_SIMPLE_POINTER_STATE pointerState;

  const auto status = s_SimplePointerProtocol->GetState(s_SimplePointerProtocol, &pointerState);
  switch(status)
  {
    case EFI_SUCCESS:
      UpdateState(&pointerState);
      break;
    case EFI_NOT_READY:
      UpdateState(nullptr);
      break;
    default:
      Logger::Println_("Error: ", PrintEfiStatus(status), " on mouse update.");
      UefiSystem::SleepForever();
  }
}

Point Mouse::Pos()
{
  return s_pos;
}

Point Mouse::Delta()
{
  return s_delta;
}

bool Mouse::Pressed()
{
  return s_leftPressed;
}

bool Mouse::LeftPressed()
{
  return s_leftPressed;
}

bool Mouse::RightPressed()
{
  return s_rightPressed;
}
