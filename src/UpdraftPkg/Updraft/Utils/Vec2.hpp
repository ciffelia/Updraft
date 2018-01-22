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

  constexpr Vec2(const double _x, const double _y)
      : x(_x), y(_y) {}

  constexpr Vec2(const Point point)
      : x(point.x), y(point.y) {}

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

  constexpr double cross(const Vec2 &other) const
  {
    return x * other.y - y * other.x;
  }

  double distanceFrom(const Vec2 &other) const
  {
    return (other - *this).length();
  }

  Vec2 normalized() const
  {
    return *this / length();
  }

  Vec2 rotated(const double angle) const
  {
    const double s = Math::Sin(angle);
    const double c = Math::Cos(angle);
    return {x * c - y * s, x * s + y * c};
  }

  Vec2 &rotate(const double angle)
  {
    return *this = rotated(angle);
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

  constexpr Vec2 operator*(const double s) const
  {
    return {x * s, y * s};
  }

  constexpr Vec2 operator/(const double s) const
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

  Vec2 &operator*=(const double s)
  {
    x *= s;
    y *= s;
    return *this;
  }

  Vec2 &operator/=(const double s)
  {
    x /= s;
    y /= s;
    return *this;
  }

  constexpr bool operator==(const Vec2 &v) const
  {
    return v.x == x && v.y == y;
  }

  constexpr bool operator!=(const Vec2 &v) const
  {
    return !(*this == v);
  }

  constexpr Point asPoint() const
  {
    return { static_cast<int32>(x), static_cast<int32>(y) };
  }
};

inline constexpr Vec2 operator*(const double s, const Vec2 &v)
{
  return {s * v.x, s * v.y};
}
