#include "Mouse.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Assert.hpp"
#include "../Graphics/Screen.hpp"

EFI_SIMPLE_POINTER_PROTOCOL *Mouse::s_SimplePointerProtocol;

uint64 Mouse::s_resolutionX, Mouse::s_resolutionY;

uint8 Mouse::s_mouseSpeed;

Point Mouse::s_pos;

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

void Mouse::UpdateState(const EFI_SIMPLE_POINTER_STATE pointerState)
{
  s_pos.x += (int32)((pointerState.RelativeMovementX / s_resolutionX) * s_mouseSpeed);
  s_pos.y += (int32)((pointerState.RelativeMovementY / s_resolutionY) * s_mouseSpeed);

  if (s_pos.x < 0)
    s_pos.x = 0;
  if (s_pos.x >= static_cast<int32>(Screen::Width()))
    s_pos.x = static_cast<int32>(Screen::Width()) - 1;
  if (s_pos.y < 0)
    s_pos.y = 0;
  if (s_pos.y >= static_cast<int32>(Screen::Height()))
    s_pos.y = static_cast<int32>(Screen::Height()) - 1;

  s_leftPressed = pointerState.LeftButton == TRUE;
  s_rightPressed = pointerState.RightButton == TRUE;
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
      UpdateState(pointerState);
      break;
    case EFI_NOT_READY:
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
