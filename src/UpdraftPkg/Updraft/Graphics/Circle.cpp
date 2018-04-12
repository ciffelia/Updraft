#include "Circle.hpp"

#include "../Utils/Math.hpp"

Circle& Circle::moveBy(const Point v)
{
  center += v;
}

Circle Circle::movedBy(const Point v) const
{
  return Circle(center + v, r);
}

void Circle::draw(const Color color) const
{
  for(int32 y = center.y - r; y < center.y + (int32)r; y++)
  {
    for(int32 x = center.x - r; x < center.x + (int32)r; x++)
    {
      if(Point(x, y).distanceFrom(center) <= r) Point(x, y).draw(color);
    }
  }
}
