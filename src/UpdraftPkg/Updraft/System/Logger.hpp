#pragma once

#include "../Utils/Format.hpp"
#include "../Graphics/Font.hpp"

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
    const char *buf = Sprintf(format, args...);

    PrintString(buf);

    delete[] buf;
  }

  template <class... Args>
  static void Print_(const Args &... args)
  {
    const char *buf = Format(args...);

    PrintString(buf);

    delete[] buf;
  }

  template <class... Args>
  static void Println_(const Args &... args)
  {
    Print_(args..., "\r\n");
  }

  static void ClearPrint();
};
