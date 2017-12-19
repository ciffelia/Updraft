#pragma once

#include "../Types.hpp"

struct Size {
  uint32 width, height;

  constexpr Size(const uint32 _width, const uint32 _height)
    : width(_width), height(_height)
  { }
};
