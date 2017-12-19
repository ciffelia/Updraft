#pragma once

#include "../Types.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "Size.hpp"

struct Rect {
  Point point;
  Size size;

  constexpr Rect(const Point _point, const Size _size)
    : point(_point)
    , size(_size)
  { }

  constexpr Rect(const uint32 x, const uint32 y, const uint32 width, const uint32 height)
    : point(x, y)
    , size(width, height)
  { }

  void draw(const Color color) const;
};
