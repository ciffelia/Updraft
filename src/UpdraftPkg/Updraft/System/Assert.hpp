#pragma once

extern "C" {
#include <Uefi.h>
}

void Assert(const bool value, const char *msg);

void AssertEfiStatus(const EFI_STATUS status, const char *msg);

template <typename T>
void AssertNotNullptr(const T *ptr, const char *msg)
{
  Assert(ptr != nullptr, msg);
}
