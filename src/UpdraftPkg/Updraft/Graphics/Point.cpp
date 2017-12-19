#include "Point.hpp"

extern "C" {
#include <Uefi.h>
#include <Protocol/GraphicsOutput.h>
}

#include "../UefiSystem.hpp"
#include "Screen.hpp"

void Point::draw(const Color color) const
{
  const uint32 width = Screen::width();

  auto *frameBufferBase = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)UefiSystem::GraphicsOutputProtocol->Mode->FrameBufferBase;
  auto *pixel = frameBufferBase + (width * y) + x;

  // const auto pixelFormat = UefiSystem::GraphicsOutputProtocol->Mode->Info->PixelFormat;
  // switch(pixelFormat) {
  //   case PixelBlueGreenRedReserved8BitPerColor:
  //     pixel->Blue = color.b;
  //     pixel->Red = color.r;
  //     break;
  //   case PixelRedGreenBlueReserved8BitPerColor:
  //     pixel->Blue = color.r;
  //     pixel->Red = color.b;
  //     break;
  // }
  //
  // pixel->Green = color.g;
  // pixel->Reserved = 0xff;

  *pixel = {color.b, color.g, color.r, 0xff};
}
