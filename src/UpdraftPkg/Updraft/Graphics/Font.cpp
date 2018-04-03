#include "Font.hpp"

#include "../System/Assert.hpp"
#include "../System/FileSystem.hpp"

uint8 Font::getGlyphWidth(const char ch) const
{
  return m_data[4 + 1024 * (ch - ' ')];
}

const uint8 *Font::getGlyphDataPtr(const char ch) const
{
  return &m_data[4 + 1024 * (ch - ' ') + 1];
}

void Font::drawGlyph(const char ch, const Point pos, const Color color) const
{
  const uint8 width = getGlyphWidth(ch);
  const uint8 *glyph = getGlyphDataPtr(ch);

  for (int y = 0; y < m_height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      const double fontAlpha = 1 - glyph[width * y + x] / 255.0;
      const double alpha = fontAlpha * (color.a / 255.0);
      Point(pos.x + x, pos.y + y).draw(Color(color, static_cast<uint8>(alpha * 255)));
    }
  }
}

Font::Font(const wchar_t *fileName)
{
  m_data = FileSystem::Read(fileName);

  Assert(
    m_data.read() == 'U' &&
    m_data.read() == 'F' &&
    m_data.read() == 'D',
    "Font data is invalid."
  );

  m_height = m_data.read();
}

void Font::draw(const CHAR8 *str, const Point pos, const Color color) const
{
  Point currentPos = pos;

  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == '\r' && str[i + 1] == '\n')
    {
      currentPos.x = pos.x;
      currentPos.y += m_height;
      i++;
      continue;
    }
    if (str[i] == '\n')
    {
      currentPos.x = pos.x;
      currentPos.y += m_height;
      continue;
    }
    if (str[i] == '\r')
    {
      currentPos.x = pos.x;
      continue;
    }

    drawGlyph(str[i], currentPos, color);

    currentPos.x += getGlyphWidth(str[i]);
  }
}
