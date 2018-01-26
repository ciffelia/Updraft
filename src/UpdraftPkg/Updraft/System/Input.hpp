#pragma once

#include "../Utils/Types.hpp"
#include "UsbKeyboard.hpp"

struct SingleKey
{
  const uint8 keyCode;
  const bool isModifierKey;

  constexpr SingleKey(const uint8 _keyCode, const bool _isModifierKey)
    : keyCode(_keyCode)
    , isModifierKey(_isModifierKey)
  { }

  bool pressed() const
  {
    return UsbKeyboard::IsPressed(keyCode, isModifierKey);
  }
};

struct DoubleKey
{
  const uint8 keyCode1, keyCode2;
  const bool isModifierKey;

  constexpr DoubleKey(const uint8 _keyCode1, const uint8 _keyCode2, const bool _isModifierKey)
    : keyCode1(_keyCode1)
    , keyCode2(_keyCode2)
    , isModifierKey(_isModifierKey)
  { }

  bool pressed() const
  {
    return
      UsbKeyboard::IsPressed(keyCode1, isModifierKey) ||
      UsbKeyboard::IsPressed(keyCode2, isModifierKey);
  }
};

namespace Input
{
  constexpr SingleKey KeyLeftCtrl(0, true);
  constexpr SingleKey KeyLeftShift(1, true);
  constexpr SingleKey KeyLeftAlt(2, true);
  constexpr SingleKey KeyLeftGui(3, true);

  constexpr SingleKey KeyRightCtrl(4, true);
  constexpr SingleKey KeyRightShift(5, true);
  constexpr SingleKey KeyRightAlt(6, true);
  constexpr SingleKey KeyRightGui(7, true);

  constexpr DoubleKey KeyCtrl(0, 4, true);
  constexpr DoubleKey KeyShift(1, 5, true);
  constexpr DoubleKey KeyAlt(2, 6, true);
  constexpr DoubleKey KeyGui(3, 7, true);

  constexpr SingleKey KeyA(0x04, false);
  constexpr SingleKey KeyB(0x05, false);
  constexpr SingleKey KeyC(0x06, false);
  constexpr SingleKey KeyD(0x07, false);
  constexpr SingleKey KeyE(0x08, false);
  constexpr SingleKey KeyF(0x09, false);
  constexpr SingleKey KeyG(0x0A, false);
  constexpr SingleKey KeyH(0x0B, false);
  constexpr SingleKey KeyI(0x0C, false);
  constexpr SingleKey KeyJ(0x0D, false);
  constexpr SingleKey KeyK(0x0E, false);
  constexpr SingleKey KeyL(0x0F, false);
  constexpr SingleKey KeyM(0x10, false);
  constexpr SingleKey KeyN(0x11, false);
  constexpr SingleKey KeyO(0x12, false);
  constexpr SingleKey KeyP(0x13, false);
  constexpr SingleKey KeyQ(0x14, false);
  constexpr SingleKey KeyR(0x15, false);
  constexpr SingleKey KeyS(0x16, false);
  constexpr SingleKey KeyT(0x17, false);
  constexpr SingleKey KeyU(0x18, false);
  constexpr SingleKey KeyV(0x19, false);
  constexpr SingleKey KeyW(0x1A, false);
  constexpr SingleKey KeyX(0x1B, false);
  constexpr SingleKey KeyY(0x1C, false);
  constexpr SingleKey KeyZ(0x1D, false);

  constexpr DoubleKey Key1(0x1E, 0x59, false);
  constexpr DoubleKey Key2(0x1F, 0x5A, false);
  constexpr DoubleKey Key3(0x20, 0x5B, false);
  constexpr DoubleKey Key4(0x21, 0x5C, false);
  constexpr DoubleKey Key5(0x22, 0x5D, false);
  constexpr DoubleKey Key6(0x23, 0x5E, false);
  constexpr DoubleKey Key7(0x24, 0x5F, false);
  constexpr DoubleKey Key8(0x25, 0x60, false);
  constexpr DoubleKey Key9(0x26, 0x61, false);
  constexpr DoubleKey Key0(0x27, 0x62, false);

  constexpr DoubleKey KeyEnter(0x28, 0x58, false);
  constexpr SingleKey KeyEscape(0x29, false);
  constexpr SingleKey KeyBackspace(0x2A, false);
  constexpr SingleKey KeyTab(0x2B, false);
  constexpr SingleKey KeySpace(0x2C, false);
  constexpr SingleKey KeyCapsLock(0x39, false);

  constexpr SingleKey KeyF1(0x3A, false);
  constexpr SingleKey KeyF2(0x3B, false);
  constexpr SingleKey KeyF3(0x3C, false);
  constexpr SingleKey KeyF4(0x3D, false);
  constexpr SingleKey KeyF5(0x3E, false);
  constexpr SingleKey KeyF6(0x3F, false);
  constexpr SingleKey KeyF7(0x40, false);
  constexpr SingleKey KeyF8(0x41, false);
  constexpr SingleKey KeyF9(0x42, false);
  constexpr SingleKey KeyF10(0x43, false);
  constexpr SingleKey KeyF11(0x44, false);
  constexpr SingleKey KeyF12(0x45, false);

  constexpr SingleKey KeyPrintScreen(0x46, false);
  constexpr SingleKey KeyScrollLock(0x47, false);
  constexpr SingleKey KeyPause(0x48, false);
  constexpr DoubleKey KeyInsert(0x49, 0x60, false);

  constexpr DoubleKey KeyHome(0x4A, 0x5F, false);
  constexpr DoubleKey KeyPageUp(0x4B, 0x61, false);
  constexpr DoubleKey KeyEnd(0x4D, 0x59, false);
  constexpr DoubleKey KeyPageDown(0x4E, 0x5B, false);

  constexpr DoubleKey KeyRight(0x4F, 0x5E, false);
  constexpr DoubleKey KeyLeft(0x50, 0x5C, false);
  constexpr DoubleKey KeyDown(0x51, 0x5A, false);
  constexpr DoubleKey KeyUp(0x52, 0x60, false);
}
