#include "Circle.hpp"

#include "Screen.hpp"
#include "../Utils/Math.hpp"

Circle& Circle::moveBy(const Point v)
{
  center += v;
  return *this;
}

Circle Circle::movedBy(const Point v) const
{
  return Circle(center + v, r);
}

void Circle::draw(const Color color) const
{
  if (center.x + (int)r < 0 || center.y + (int)r < 0)
    return;
  if (center.x - (int)r > (int)Screen::Width() || center.y - (int)r > (int)Screen::Height())
    return;

  for(int32 y = center.y - (int)r; y < center.y + (int)r; y++)
  {
    for (int32 x = center.x - (int)r; x < center.x + (int)r; x++)
    {
      if(Point(x, y).distanceFrom(center) <= r) Point(x, y).draw(color);
    }
  }
}
