#pragma once

#include "../Types.hpp"
#include "Color.hpp"
#include "Point.hpp"

struct Circle {
  Point pos;
  uint32 r;

  constexpr Circle(const Point _pos, const uint32 _r)
    : pos(_pos)
    , r(_r)
  { }

  constexpr Circle(const uint32 x, const uint32 y, const uint32 _r)
    : pos(x, y)
    , r(_r)
  { }

  void draw(const Color color) const;
};
