/*
 * This file contains codes from https://github.com/Siv3D/OpenSiv3D
 * For more information, please see README.md
 */

#pragma once

#include "Types.hpp"
#include "Math.hpp"
#include "Vec2.hpp"

class Circular
{
  static constexpr double Clamp(double theta)
  {
    return theta <= -Math::Pi ? theta + Math::TwoPi : theta;
  }

public:
  double r, theta;

  Circular() = default;

  constexpr Circular(double _r, double _theta)
      : r(_r), theta(_theta) {}

  Circular(const Vec2 &v)
      : r(v.length()), theta(Clamp(Math::Atan2(v.y, v.x))) {}

  constexpr Circular operator+() const
  {
    return *this;
  }

  constexpr Circular operator-() const
  {
    return {r, Clamp(theta - Math::Pi)};
  }

  Vec2 operator+(const Vec2 &v) const
  {
    return toVec2() + v;
  }

  Vec2 operator-(const Vec2 &v) const
  {
    return toVec2() - v;
  }

  Vec2 toVec2() const
  {
    return {Math::Cos(theta) * r, Math::Sin(theta) * r};
  }

  operator Vec2() const
  {
    return toVec2();
  }
};
