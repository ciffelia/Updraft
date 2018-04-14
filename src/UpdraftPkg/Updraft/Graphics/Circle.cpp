#include "Circle.hpp"

#include "Screen.hpp"
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
  if (center.x + r < 0 || center.y + r < 0)
    return;
  if (center.x - r > (int)Screen::Width() || center.y - r > (int)Screen::Height())
    return;

  for(int32 y = center.y - (int)r; y < center.y + (int32)r; y++)
  {
    for (int32 x = center.x - (int)r; x < center.x + (int32)r; x++)
    {
      if(Point(x, y).distanceFrom(center) <= r) Point(x, y).draw(color);
    }
  }
}
