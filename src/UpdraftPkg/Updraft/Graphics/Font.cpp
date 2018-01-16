#include "Font.hpp"

#include "../System/Assert.hpp"
#include "../System/FileSystem.hpp"
#include "Color.hpp"

uint8 Font::getGlyphWidth(const char ch) const
{
  return m_data[4 + 1024 * (ch - ' ')];
}

uint8 *Font::getGlyphDataPtr(const char ch) const
{
  return &m_data[4 + 1024 * (ch - ' ') + 1];
}

void Font::drawGlyph(const char ch, const Point pos) const
{
  const uint8 width = getGlyphWidth(ch);
  const uint8 *glyph = getGlyphDataPtr(ch);

  for (int y = 0; y < m_height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      const uint8 grayScale = glyph[width * y + x];
      Point(pos.x + x, pos.y + y).draw(Color(grayScale, grayScale, grayScale));
    }
  }
}

Font::Font(CHAR16 *fileName)
{
  uintn bufSize = 4 + 1024 * ('~' - ' ' + 1);
  m_data = new uint8[bufSize];

  FileSystem::Read(fileName, &bufSize, (void *)m_data);

  Assert(m_data[0] == 'U' && m_data[1] == 'F' && m_data[2] == 'D', "Font data is invalid.");

  m_height = m_data[3];
}

Font::~Font()
{
  delete[] m_data;
}

void Font::draw(const CHAR8 *str, const Point pos) const
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

    drawGlyph(str[i], currentPos);

    currentPos.x += getGlyphWidth(str[i]);
  }
}
