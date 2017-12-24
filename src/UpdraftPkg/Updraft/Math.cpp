#include "Math.hpp"

#include <math.h>

namespace Math {
  double Pow(const double x, const double y)
  {
    return pow(x, y);
  }

  double Square(const double x)
  {
    return x * x;
  }

  double Sqrt(const double x)
  {
    return sqrt(x);
  }
}
