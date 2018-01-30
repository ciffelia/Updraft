#pragma once

class Point;
struct Rect;
struct Vec2;

namespace Geometry
{
  bool Contains(const Rect rect, const Point p);
  
  bool Contains(const Rect rect, const Vec2 v);
}
