#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "../Utils/Types.hpp"

class Graphics {
  static EFI_GRAPHICS_OUTPUT_PROTOCOL *s_GraphicsOutputProtocol;

  static void LocateGOP();

  static void CheckPixelFormat();

  static bool IsProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution);

  static uint32 GetProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution);

  static void SetVideoMode(const uint32 mode);

public:
  static void Initialize();

  static EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsOutputProtocol();
};
