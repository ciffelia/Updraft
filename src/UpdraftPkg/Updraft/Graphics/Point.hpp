#pragma once

#include "../Utils/Types.hpp"
#include "Color.hpp"

class Point {
  uint8 blend(const uint8 dest, const uint8 src, const uint8 alpha) const;

public:
  int32 x, y;

  Point() = default;

  constexpr Point(const int32 _x, const int32 _y)
    : x(_x), y(_y)
  { }

  double distanceFrom(const Point pos) const;

  void draw(const Color color) const;

  constexpr Point operator+() const;

  constexpr Point operator-() const;

  constexpr Point operator+(const Point &other) const;

  constexpr Point operator-(const Point &other) const;

  constexpr Point operator*(const double s) const;

  constexpr Point operator/(const double s) const;

  Point &operator+=(const Point &other);

  Point &operator-=(const Point &other);

  Point &operator*=(const double s);

  Point &operator/=(const double s);

  constexpr bool operator==(const Point &other) const;

  constexpr bool operator!=(const Point &other) const;
};

constexpr Point operator*(double s, const Point &p);
