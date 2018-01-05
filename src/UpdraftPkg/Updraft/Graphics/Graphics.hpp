#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "../Utils/Types.hpp"
#include "Color.hpp"
#include "ColorPalette.hpp"

class Graphics {
  static EFI_GRAPHICS_OUTPUT_PROTOCOL *s_GraphicsOutputProtocol;

  static Color s_backgroundColor;

  static void LocateGOP();

  static void CheckPixelFormat();

  static bool IsProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution);

  static uint32 GetProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution);

  static void SetVideoMode(const uint32 mode);

public:
  static void Initialize(const Color backgroundColor = Palette::Navy);

  static void Update();

  static EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsOutputProtocol();

  static void BackgroundColor(const Color backgroundColor);

  static Color BackgroundColor();
};
