#pragma once

#include "PrintEfiStatus.hpp"
#include "../Utils/Vec2.hpp"
#include "../Utils/Circular.hpp"
#include "../Graphics/Circle.hpp"
#include "../Graphics/Color.hpp"
#include "../Graphics/Point.hpp"
#include "../Graphics/Rect.hpp"
#include "../Graphics/Size.hpp"
#include "../Graphics/Font.hpp"

#include <stdio.h>

// Library/UefiLib.h にある Print() のラッパー
// Siv3Dの Print(), Println(), ClearPrint() と同様の動作をする (https://goo.gl/vG3ZB7)
class Logger
{
  static const Font *s_font;

  static char s_log[512];
  static uint16 s_caret;

  static void PrintChar(const char ch);

  static void PrintString(const char *str);

public:
  static void Initialize();

  static void Update();

  static void Dispose();

  template <class... Args>
  static void Printf(const char *format, const Args &... args)
  {
    const int bufSize = snprintf(nullptr, 0, format, args...) + 1;

    char *buf = new char[bufSize];

    sprintf(buf, format, args...);

    PrintString(buf);

    delete[] buf;
  }

  static void Print_();

  static void Print_(const int8 value);

  static void Print_(const int16 value);

  static void Print_(const int32 value);

  static void Print_(const int64 value);

  static void Print_(const double value);

  static void Print_(const uint8 value);

  static void Print_(const uint16 value);

  static void Print_(const uint32 value);

  static void Print_(const uint64 value);

  static void Print_(const CHAR8 *value);

  static void Print_(const CHAR16 *value);

  static void Print_(const bool value);

  static void Print_(const PrintEfiStatus value);

  static void Print_(const Vec2 value);

  static void Print_(const Circular value);

  static void Print_(const Circle value);

  static void Print_(const Color value);

  static void Print_(const Point value);

  static void Print_(const Rect value);

  static void Print_(const Size value);

  template <class Type, class... Args>
  static void Print_(const Type &value, const Args &... args)
  {
    Print_(value);
    Print_(args...);
  }

  template <class... Args>
  static void Println_(const Args &... args)
  {
    Print_(args..., "\r\n");
  }

  static void ClearPrint();
};
