#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "Types.hpp"

class UefiSystem {
  static EFI_SYSTEM_TABLE *SystemTable;

  static EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutputProtocol;

  static void releaseWatchdogTimer();

  static void locateGOP();

  static void checkPixelFormat();

  static bool isProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution);

  static uint32 getProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution);

  static void setVideoMode(const uint32 mode);

public:
  static void initialize(EFI_SYSTEM_TABLE *ST);

  static EFI_SYSTEM_TABLE* getSystemTable();

  static EFI_GRAPHICS_OUTPUT_PROTOCOL* getGraphicsOutputProtocol();

  static void sleepForever();
};
