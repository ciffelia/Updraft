#pragma once

extern "C" {
#include <Uefi.h>
}

#include "../Utils/Types.hpp"
#include "../Utils/BinaryArray.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "ColorPalette.hpp"

class Font
{
  BinaryArray m_data;

  Array<Array<double>> m_alphaData;

  uint8 m_height;

  uint8 getGlyphWidth(const char ch) const;

  const uint8 *getGlyphDataPtr(const char ch) const;

  uint8 drawGlyph(const char ch, const Point pos, const Color color, const double scale) const;

  void calcAlphaData();

public:
  Font(const wchar_t *fileName);

  void draw(const CHAR8 *str, const Point pos, const Color color = Palette::Black, const double scale = 1) const;
};
