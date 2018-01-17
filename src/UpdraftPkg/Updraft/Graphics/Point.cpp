#include "Point.hpp"

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "../Graphics/Graphics.hpp"
#include "../Utils/Math.hpp"
#include "Screen.hpp"

double Point::distanceFrom(const Point pos) const
{
  return Math::Sqrt(Math::Square(pos.x - x) + Math::Square(pos.y - y));
}

void Point::draw(const Color color) const
{
  const uint32 width = Screen::Width(), height = Screen::Height();

  if (x < 0 || x >= static_cast<int32>(width) || y < 0 || y >= static_cast<int32>(height))
    return;

  const auto blend = [&](const uint8 dest, const uint8 src, const uint8 alpha) {
    return static_cast<uint8>(dest * (1 - alpha / 255.0) + src * alpha / 255.0);
  };

  auto *frameBufferBase = Graphics::BltBuffer();
  auto *pixel = frameBufferBase + (width * y) + x;

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
