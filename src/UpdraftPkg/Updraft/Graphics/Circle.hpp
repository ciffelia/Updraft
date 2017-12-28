#pragma once

#include "../System/Types.hpp"
#include "Color.hpp"
#include "Point.hpp"

struct Circle {
  Point center;
  uint32 r;

  constexpr Circle() = default;

  constexpr Circle(const Point _center, const uint32 _r)
    : center(_center)
    , r(_r)
  { }

  constexpr Circle(const int32 x, const int32 y, const uint32 _r)
    : center(x, y)
    , r(_r)
  { }

  void draw(const Color color) const;
};
