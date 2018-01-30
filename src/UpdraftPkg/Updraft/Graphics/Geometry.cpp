#include "Geometry.hpp"

#include "Rect.hpp"
#include "Point.hpp"
#include "../Utils/Vec2.hpp"

bool Geometry::Contains(const Rect rect, const Point p)
{
  return rect.pos.x <= p.x &&
         rect.pos.y <= p.y &&
         p.x <= (rect.pos.x + (int32)rect.size.width) &&
         p.y <= (rect.pos.y + (int32)rect.size.height);
}

bool Geometry::Contains(const Rect rect, const Vec2 v)
{
  return rect.pos.x <= v.x &&
         rect.pos.y <= v.y &&
         v.x <= (rect.pos.x + (int32)rect.size.width) &&
         v.y <= (rect.pos.y + (int32)rect.size.height);
}
