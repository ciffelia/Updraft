#pragma once

#include "../Types.hpp"
#include "Color.hpp"

struct Point {
  uint32 x, y;

  constexpr Point() = default;

  constexpr Point(const uint32 _x, const uint32 _y)
    : x(_x), y(_y)
  { }

  void draw(const Color color) const;
};
