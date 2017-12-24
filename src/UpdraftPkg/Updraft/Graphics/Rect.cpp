#include "Rect.hpp"

void Rect::draw(const Color color) const
{
  for(int32 y = pos.y; y < pos.y + size.height; y++)
  {
    for(int32 x = pos.x; x < pos.x + size.width; x++)
    {
      Point(x, y).draw(color);
    }
  }
}
