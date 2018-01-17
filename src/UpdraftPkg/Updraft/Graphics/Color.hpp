#pragma once

#include "../Utils/Types.hpp"

struct Color {
  uint8 r, g, b, a;

  constexpr Color() = default;

  constexpr Color(const uint8 _r, const uint8 _g, const uint8 _b, const uint8 _a = 255)
    : r(_r), g(_g), b(_b), a(_a)
  { }

  constexpr Color(const Color &rgb, const uint8 _a)
    : r(rgb.r), g(rgb.g), b(rgb.b), a(_a)
  { }

  constexpr Color(const uint8 rgb, const uint8 _a = 255)
    : r(rgb), g(rgb), b(rgb), a(_a)
  { }
};
