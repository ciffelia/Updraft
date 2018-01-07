/*
 * This file contains codes from https://qiita.com/Reputeless/items/96226cfe1282a014b147
 * For more information, please see README.md
 */

#pragma once

#include "Math.hpp"
#include "../Graphics/Point.hpp"

struct Vec2
{
  double x;
  double y;

  Vec2() = default;

  constexpr Vec2(double _x, double _y)
      : x(_x), y(_y) {}

  double length() const
  {
    return Math::Sqrt(lengthSquare());
  }

  constexpr double lengthSquare() const
  {
    return dot(*this);
  }

  constexpr double dot(const Vec2 &other) const
  {
    return x * other.x + y * other.y;
  }

  double distanceFrom(const Vec2 &other) const
  {
    return (other - *this).length();
  }

  Vec2 normalized() const
  {
    return *this / length();
  }

  constexpr bool isZero() const
  {
    return x == 0.0 && y == 0.0;
  }

  constexpr Vec2 operator+() const
  {
    return *this;
  }

  constexpr Vec2 operator-() const
  {
    return {-x, -y};
  }

  constexpr Vec2 operator+(const Vec2 &other) const
  {
    return {x + other.x, y + other.y};
  }

  constexpr Vec2 operator-(const Vec2 &other) const
  {
    return {x - other.x, y - other.y};
  }

  constexpr Vec2 operator*(double s) const
  {
    return {x * s, y * s};
  }

  constexpr Vec2 operator/(double s) const
  {
    return {x / s, y / s};
  }

  Vec2 &operator+=(const Vec2 &other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 &operator-=(const Vec2 &other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2 &operator*=(double s)
  {
    x *= s;
    y *= s;
    return *this;
  }

  Vec2 &operator/=(double s)
  {
    x /= s;
    y /= s;
    return *this;
  }

  constexpr Point asPoint() const
  {
    return Point(x, y);
  }
};

inline constexpr Vec2 operator*(double s, const Vec2 &v)
{
  return {s * v.x, s * v.y};
}
