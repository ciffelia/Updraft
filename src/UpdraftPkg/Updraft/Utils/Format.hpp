#pragma once

extern "C" {
#include <Uefi.h>
#include <Library/BaseLib.h>
}

#include <stdio.h>

#include "../System/Assert.hpp"
#include "../System/PrintEfiStatus.hpp"
#include "../Graphics/Circle.hpp"
#include "../Graphics/Color.hpp"
#include "../Graphics/Point.hpp"
#include "../Graphics/Rect.hpp"
#include "../Graphics/Size.hpp"
#include "Types.hpp"
#include "Vec2.hpp"
#include "Circular.hpp"

template <class... Args>
char* Sprintf(const char *format, const Args &... args)
{
  const int bufSize = snprintf(nullptr, 0, format, args...) + 1;

  char *buf = new char[bufSize];

  sprintf(buf, format, args...);

  return buf;
}

char* Format();

char* Format(const int8 value);

char* Format(const int16 value);

char* Format(const int32 value);

char* Format(const int64 value);

char* Format(const double value);

char* Format(const uint8 value);

char* Format(const uint16 value);

char* Format(const uint32 value);

char* Format(const uint64 value);

char* Format(const CHAR8 *value);

char* Format(const CHAR16 *value);

char* Format(const bool value);

char* Format(const PrintEfiStatus value);

char* Format(const Vec2 value);

char* Format(const Circular value);

char* Format(const Circle value);

char* Format(const Color value);

char* Format(const Point value);

char* Format(const Rect value);

char* Format(const Size value);

template <class Type, class... Args>
char* Format(const Type &value, const Args &... args)
{
  const char *a = Format(value);
  const char *b = Format(args...);

  const size_t size = ::AsciiStrLen(a) + ::AsciiStrLen(b) + 1;
  char *res = new char[size];

  AssertEfiStatus(::AsciiStrCpyS(res, size, a), "Failed to copy string.");
  AssertEfiStatus(::AsciiStrCatS(res, size, b), "Failed to concat string.");

  delete[] a, b;

  return res;
}
