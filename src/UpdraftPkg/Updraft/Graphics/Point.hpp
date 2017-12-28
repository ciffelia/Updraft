#pragma once

#include "../System/Types.hpp"
#include "Color.hpp"

struct Point {
  int32 x, y;

  constexpr Point() = default;

  constexpr Point(const int32 _x, const int32 _y)
    : x(_x), y(_y)
  { }

  double distanceFrom(const Point pos) const;

  void draw(const Color color) const;
};
