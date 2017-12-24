#include "Math.hpp"

namespace Math {
  int Pow(const int x, const int y)
  {
    int ret = 1;
    for(int i = 0; i < y; i++) ret *= x;
    return ret;
  }
}
