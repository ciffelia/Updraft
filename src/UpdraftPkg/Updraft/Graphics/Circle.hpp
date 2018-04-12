#pragma once

#include "../Utils/Types.hpp"
#include "Color.hpp"
#include "Point.hpp"

struct Circle {
  Point center;
  uint32 r;

  Circle() = default;

  constexpr Circle(const Point _center, const uint32 _r)
    : center(_center)
    , r(_r)
  { }

  constexpr Circle(const int32 x, const int32 y, const uint32 _r)
    : center(x, y)
    , r(_r)
  { }

  Circle& moveBy(const Point v);

  Circle movedBy(const Point v) const;

  void draw(const Color color) const;
};
