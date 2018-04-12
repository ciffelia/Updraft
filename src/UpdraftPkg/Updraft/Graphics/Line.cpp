#include "Line.hpp"

#include "../Utils/Utility.hpp"

Line &Line::moveBy(const Vec2 v)
{
  begin += v;
  end += v;
}

Line Line::movedBy(const Vec2 v) const
{
  return Line(begin + v, end + v);
}

// Bresenham's line algorithm: https://ja.wikipedia.org/wiki/ブレゼンハムのアルゴリズム
void Line::draw(const Color color) const
{
  int x0 = static_cast<int>(begin.x), y0 = static_cast<int>(begin.y),
      x1 = static_cast<int>(end.x), y1 = static_cast<int>(end.y);

  const bool steep = Math::Abs(y1 - y0) > Math::Abs(x1 - x0);

  if (steep)
  {
    Swap(x0, y0);
    Swap(x1, y1);
  }
  if (x0 > x1)
  {
    Swap(x0, x1);
    Swap(y0, y1);
  }

  const int deltax = x1 - x0, deltay = Math::Abs(y1 - y0);
  int error = deltax / 2;

  const int ystep = (y0 < y1) ? 1 : -1;

  int y = y0;

  for (int x = x0; x <= x1; x++)
  {
    if (steep)
      Point(y, x).draw(color);
    else
      Point(x, y).draw(color);
    
    error = error - deltay;
    if (error < 0)
    {
      y += ystep;
      error += deltax;
    }
  }
}
