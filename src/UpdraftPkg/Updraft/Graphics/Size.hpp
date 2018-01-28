#pragma once

#include "../Utils/Types.hpp"

struct Size {
  uint32 width, height;

  Size() = default;

  constexpr Size(const uint32 _width, const uint32 _height)
    : width(_width), height(_height)
  { }
};
