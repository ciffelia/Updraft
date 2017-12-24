#include "Circle.hpp"

#include "../Math.hpp"

void Circle::draw(const Color color) const
{
  for(int32 y = pos.y - r; y < pos.y + r; y++)
  {
    for(int32 x = pos.x - r; x < pos.x + r; x++)
    {
      if(Point(x, y).distanceFrom(pos) <= r) Point(x, y).draw(color);
    }
  }
}
