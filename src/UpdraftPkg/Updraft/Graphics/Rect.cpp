#include "Rect.hpp"

void Rect::draw(const Color color) const
{
  for(uint32 y = pos.y; y < pos.y + size.height; y++)
  {
    for(uint32 x = pos.x; x < pos.x + size.width; x++)
    {
      Point(x, y).draw(color);
    }
  }
}
