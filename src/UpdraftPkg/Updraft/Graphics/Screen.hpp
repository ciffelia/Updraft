#pragma once

#include "../Utils/Types.hpp"
#include "Point.hpp"
#include "Rect.hpp"
#include "Size.hpp"

namespace Screen {
  Size Size();

  Point Center();

  Rect Rect();

  uint32 Width();
  uint32 Height();
};
