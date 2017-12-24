#pragma once

#include "Graphics/Color.hpp"
#include "Graphics/Point.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Size.hpp"

// Library/UefiLib.h にある Print() のラッパー
// Siv3Dの Print(), Println(), ClearPrint() と同様の動作をする (https://goo.gl/vG3ZB7)
namespace Logger {
  void Print_();

  void Print_(const CHAR8 value);

  // void Print_(const CHAR16 value);

  void Print_(const int8 value);

  void Print_(const int16 value);

  void Print_(const int32 value);

  void Print_(const int64 value);

  void Print_(const double value);

  void Print_(const uint8 value);

  void Print_(const uint16 value);

  void Print_(const uint32 value);

  void Print_(const uint64 value);

  void Print_(const void *value);

  void Print_(const CHAR8 *value);

  void Print_(const CHAR16 *value);

  void Print_(const GUID *value);

  void Print_(const EFI_TIME *value);

  // void Print_(const RETURN_STATUS value);

  void Print_(const bool value);

  void Print_(const Color value);

  void Print_(const Point value);

  void Print_(const Rect value);

  void Print_(const Size value);

  template <class Type, class ... Args>
  void Print_(const Type& value, const Args& ... args)
  {
    Print_(value);
    Print_(args...);
  }

  template <class ... Args>
  void Println_(const Args& ... args)
  {
    Print_(args..., "\r\n");
  }

  void ClearPrint();
};
