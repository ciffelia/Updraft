#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

class UefiSystem {
  static void release_watchdog_timer();

  static void locate_gop();

  static void check_pixel_format();

  static void clear_screen();

public:
  static EFI_SYSTEM_TABLE *SystemTable;

  static EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutputProtocol;

  static void initialize(EFI_SYSTEM_TABLE *ST);

  static void loop_forever();
};
