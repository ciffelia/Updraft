#pragma once

#include "../Types.hpp"
#include "Color.hpp"
#include "Point.hpp"

struct Circle {
  Point pos;
  uint32 r;

  constexpr Circle() = default;

  constexpr Circle(const Point _pos, const uint32 _r)
    : pos(_pos)
    , r(_r)
  { }

  constexpr Circle(const int32 x, const int32 y, const uint32 _r)
    : pos(x, y)
    , r(_r)
  { }

  void draw(const Color color) const;
};
