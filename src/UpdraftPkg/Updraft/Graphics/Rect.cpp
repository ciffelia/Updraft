#include "Rect.hpp"

Rect& Rect::moveBy(const Point v)
{
  pos += v;
}

Rect Rect::movedBy(const Point v) const
{
  return Rect(pos + v, size);
}

void Rect::draw(const Color color) const
{
  for(int32 y = pos.y; y < pos.y + (int32)size.height; y++)
  {
    for(int32 x = pos.x; x < pos.x + (int32)size.width; x++)
    {
      Point(x, y).draw(color);
    }
  }
}
