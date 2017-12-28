#pragma once

#include "../System/Types.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "Size.hpp"

namespace Screen {
  Size size();

  Point center();

  Rect rect();

  uint32 width();
  uint32 height();
};
