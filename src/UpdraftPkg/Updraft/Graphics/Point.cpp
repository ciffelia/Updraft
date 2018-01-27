#include "Point.hpp"

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "../Graphics/Graphics.hpp"
#include "../Utils/Math.hpp"
#include "Screen.hpp"

uint8 Point::blend(const uint8 dest, const uint8 src, const uint8 alpha) const
{
  return (alpha == 255)
    ? src
    : static_cast<uint8>(dest * (1 - alpha / 255.0) + src * alpha / 255.0);
}

double Point::distanceFrom(const Point pos) const
{
  return Math::Sqrt(Math::Square(pos.x - x) + Math::Square(pos.y - y));
}

void Point::draw(const Color color) const
{
  const uint32 width = Screen::Width(), height = Screen::Height();

  if (x < 0 || x >= static_cast<int32>(width) || y < 0 || y >= static_cast<int32>(height))
    return;

  if (color.a == 0)
    return;

  auto *pixel = Graphics::BltBuffer() + (width * y) + x;

  const auto pixelFormat = Graphics::GraphicsOutputProtocol()->Mode->Info->PixelFormat;
  switch(pixelFormat) {
    case PixelBlueGreenRedReserved8BitPerColor:
      *pixel = {
        blend(pixel->Blue, color.b, color.a),
        blend(pixel->Green, color.g, color.a),
        blend(pixel->Red, color.r, color.a),
        0xff
      };
      break;
    case PixelRedGreenBlueReserved8BitPerColor:
      *pixel = {
        blend(pixel->Blue, color.r, color.a),
        blend(pixel->Green, color.g, color.a),
        blend(pixel->Red, color.b, color.a),
        0xff
      };
      break;
  }
}

constexpr Point Point::operator+() const
{
  return *this;
}

constexpr Point Point::operator-() const
{
  return {-x, -y};
}

constexpr Point Point::operator+(const Point &other) const
{
  return {x + other.x, y + other.y};
}

constexpr Point Point::operator-(const Point &other) const
{
  return *this + (-other);
}

constexpr Point Point::operator*(const double s) const
{
  return {static_cast<int32>(x * s), static_cast<int32>(y * s)};
}

constexpr Point Point::operator/(const double s) const
{
  return *this * (1 / s);
}

Point &Point::operator+=(const Point &other)
{
  *this = *this + other;
  return *this;
}

Point &Point::operator-=(const Point &other)
{
  *this = *this - other;
  return *this;
}

Point &Point::operator*=(const double s)
{
  *this = *this * s;
  return *this;
}

Point &Point::operator/=(const double s)
{
  *this = *this / s;
  return *this;
}

constexpr bool Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

constexpr bool Point::operator!=(const Point &other) const
{
  return !(*this == other);
}

constexpr Point operator*(double s, const Point &p)
{
  return {static_cast<int32>(s * p.x), static_cast<int32>(s * p.y)};
}
