#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/SimplePointer.h>
}

#include "../Graphics/Point.hpp"

class Mouse {
  static EFI_SIMPLE_POINTER_PROTOCOL *s_SimplePointerProtocol;

  static uint64 s_resolutionX, s_resolutionY;

  static uint8 s_mouseSpeed;

  static Point s_pos, s_delta;

  static bool s_leftPressed, s_rightPressed;

  static void LocateSimplePointerProtocol();

  static void ResetPointerDevice();

  static void CheckPointerDevice();

  static void UpdateState(const EFI_SIMPLE_POINTER_STATE* pointerState = nullptr);

public:
  static void Initialize();

  static void Update();

  static Point Pos();

  static Point Delta();

  static bool Pressed();

  static bool LeftPressed();

  static bool RightPressed();
};
