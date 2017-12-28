#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "Types.hpp"

class UefiSystem {
  static EFI_EVENT timerEvent;

  static EFI_EVENT eventList[1];

  static uintn eventIndex;

  static void releaseWatchdogTimer();

  static void locateGOP();

  static void checkPixelFormat();

  static bool isProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution);

  static uint32 getProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution);

  static void setVideoMode(const uint32 mode);

  static void setupTimerEvent();

public:
  static EFI_SYSTEM_TABLE *SystemTable;

  static EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutputProtocol;

  static uint8 fps;

  static uint32 frameCount;

  static void initialize(EFI_SYSTEM_TABLE *ST);

  static bool update();

  static void loopForever();
};
