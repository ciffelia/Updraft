#include "Rect.hpp"

void Rect::draw(const Color color) const
{
  for(uint32 y = point.y; y < point.y + size.height; y++)
  {
    for(uint32 x = point.x; x < point.x + size.width; x++)
    {
      Point(x, y).draw(color);
    }
  }
}
