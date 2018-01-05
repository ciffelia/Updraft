#pragma once

extern "C" {
#include <Uefi.h>
}

class UefiSystem {
  static EFI_SYSTEM_TABLE *s_SystemTable;

  static void ReleaseWatchdogTimer();

public:
  static void Initialize(EFI_SYSTEM_TABLE *ST);

  static EFI_SYSTEM_TABLE* SystemTable();

  static void SleepForever();
};
