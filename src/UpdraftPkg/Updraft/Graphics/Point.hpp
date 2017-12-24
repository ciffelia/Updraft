#pragma once

#include "../Types.hpp"
#include "Color.hpp"

struct Point {
  int32 x, y;

  constexpr Point() = default;

  constexpr Point(const int32 _x, const int32 _y)
    : x(_x), y(_y)
  { }

  void draw(const Color color) const;
};
