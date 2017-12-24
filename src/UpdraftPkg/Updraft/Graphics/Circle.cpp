#include "Circle.hpp"

#include "../Math.hpp"

void Circle::draw(const Color color) const
{
  for(int32 y = pos.y - r; y < pos.y + r; y++)
  {
    for(int32 x = pos.x - r; x < pos.x + r; x++)
    {
      if(Math::Pow(x - (int32)pos.x, 2) + Math::Pow(y - (int32)pos.y, 2) <= Math::Pow(r, 2)) Point(x, y).draw(color);
    }
  }
}
