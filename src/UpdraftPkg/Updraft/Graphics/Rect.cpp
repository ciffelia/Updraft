#include "Rect.hpp"

#include "Screen.hpp"

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
  if (pos.x + size.width < 0 || pos.y + size.height < 0)
    return;
  if (pos.x > (int)Screen::Width() || pos.y > (int)Screen::Height())
    return;

  for(int32 y = pos.y; y < pos.y + (int32)size.height; y++)
  {
    for(int32 x = pos.x; x < pos.x + (int32)size.width; x++)
    {
      Point(x, y).draw(color);
    }
  }
}
