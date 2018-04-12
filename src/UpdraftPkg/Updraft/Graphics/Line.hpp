#pragma once

#include "../Utils/Vec2.hpp"
#include "../Utils/Math.hpp"

struct Line
{
  Vec2 begin, end;

  Line() = default;

  constexpr Line(const double x1, const double y1, const double x2, const double y2)
    : begin(x1, y1)
    , end(x2, y2)
  { }

  constexpr Line(const Vec2 _begin, const Vec2 _end)
    : begin(_begin)
    , end(_end)
  { }

  constexpr Line(const Vec2 _begin, const double x2, const double y2)
    : begin(_begin)
    , end(x2, y2)
  { }

  constexpr Line(const double x1, const double y1, const Vec2 _end)
    : begin(x1, y1)
    , end(_end)
  { }

  constexpr bool operator==(const Line &l) const
  {
    return begin == l.begin && end == l.end;
  }

  constexpr bool operator!=(const Line &l) const
  {
    return !(*this == l);
  }

  constexpr Vec2 vector() const
  {
    return end - begin;
  }

  double length() const
  {
    return begin.distanceFrom(end);
  }

  // http://www.zengeren.com/content/data/05/05_2DCollision.pdf
  Vec2 closest(const Vec2 &p) const
  {
    const Vec2 a = begin, b = end;
    const Vec2 ab = (b - a);
    const Vec2 ap = (p - a);
    const Vec2 bp = (p - b);

    if (ab.dot(ap) <= 0)
      return a;

    if (ab.dot(bp) >= 0)
      return b;

    const double aq = ap.dot(ab) / ab.length();

    return a + ab * (aq / ab.length());
  }

  double distanceFrom(const Vec2 &p) const
  {
    const Vec2 a = begin, b = end;
    const Vec2 ab = (b - a);
    const Vec2 ap = (p - a);
    const Vec2 bp = (p - b);

    if (ab.dot(ap) <= 0)
      return ap.length();

    if (ab.dot(bp) >= 0)
      return bp.length();

    const double cross = ap.cross(ab);

    return Math::Abs(cross) / ab.length();
  }

  Line& moveBy(const Vec2 v);

  Line movedBy(const Vec2 v) const;

  void draw(const Color color) const;
};
