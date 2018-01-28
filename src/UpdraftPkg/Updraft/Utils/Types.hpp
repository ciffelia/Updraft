#pragma once

extern "C" {
#include <Uefi.h>
}

#include <stddef.h>

using int8 = INT8;
using int16 = INT16;
using int32 = INT32;
using int64 = INT64;
using intn = INTN;

using uint8 = UINT8;
using uint16 = UINT16;
using uint32 = UINT32;
using uint64 = UINT64;
using uintn = UINTN;

using wchar_t = _EFI_WCHAR_T;
