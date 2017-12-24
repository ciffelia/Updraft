#pragma once

#include "../Types.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "Size.hpp"

struct Rect {
  Point pos;
  Size size;

  constexpr Rect() = default;

  constexpr Rect(const Point _pos, const Size _size)
    : pos(_pos)
    , size(_size)
  { }

  constexpr Rect(const int32 x, const int32 y, const uint32 width, const uint32 height)
    : pos(x, y)
    , size(width, height)
  { }

  void draw(const Color color) const;
};
