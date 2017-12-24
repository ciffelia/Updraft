#include "Circle.hpp"

#include "../Math.hpp"

void Circle::draw(const Color color) const
{
  for(uint32 y = pos.y - r; y < pos.y + r; y++)
  {
    for(uint32 x = pos.x - r; x < pos.x + r; x++)
    {
      if(Math::Pow(x - pos.x, 2) + Math::Pow(y - pos.y, 2) < Math::Pow(r, 2)) Point(x, y).draw(color);
    }
  }
}
