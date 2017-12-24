#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "Types.hpp"

class UefiSystem {
  static void release_watchdog_timer();

  static void locate_gop();

  static void check_pixel_format();

  static bool is_proper_graphics_mode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution);

  static uint32 get_proper_graphics_mode(const uint32 horizontalResolution, const uint32 verticalResolution);

  static void set_video_mode(const uint32 mode);

public:
  static EFI_SYSTEM_TABLE *SystemTable;

  static EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutputProtocol;

  static void initialize(EFI_SYSTEM_TABLE *ST);

  static void loop_forever();
};
