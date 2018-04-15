#include "Stage.hpp"

#include "Utils/Format.hpp"
#include "Utils/Utility.hpp"
#include "Graphics/Screen.hpp"
#include "Graphics/Graphics.hpp"

Vec2 Stage::size()
{
  return m_stageSize;
}

Point& Stage::scrollPos()
{
  return m_scrollPos;
}

Array<Line>& Stage::lines()
{
  return m_lines;
}

const Array<Line>& Stage::lines() const
{
  return m_lines;
}

Array<Rect>& Stage::updrafts()
{
  return m_updrafts;
}

const Array<Rect>& Stage::updrafts() const
{
  return m_updrafts;
}

bool Stage::isInStage(const Vec2 pos)
{
  return 0 < pos.x &&
         pos.x < m_stageSize.x &&
         0 < pos.y &&
         pos.y < m_stageSize.y;
}

bool Stage::isInUpdraft(const Vec2 pos)
{
  for (const auto &updraft : m_updrafts)
  {
    if (updraft.contains(pos))
      return true;
  }

  return false;
}

void Stage::update(const PlayerParams playerParams)
{
  m_player.update(playerParams);
}

void Stage::draw() const
{
  const int xStart = m_scrollPos.x,
            xEnd = Min((int)m_stageSize.x, (int)(m_scrollPos.x + Screen::Width())),
            yStart = m_scrollPos.y,
            yEnd = Min((int)m_stageSize.y, (int)(m_scrollPos.y + Screen::Height()));
  int i = 0;

  for (int y = yStart; y < yEnd; ++y)
  {
    for (int x = xStart; x < xEnd; ++x)
    {
      if ((x % 400 < 200) != (y % 400 < 200))
        Graphics::PlotBltBuffer(i, Palette::Pink);
      else
        Graphics::PlotBltBuffer(i, Palette::Lightpink);
      i++;
    }
  }

  for (const auto &updraft : m_updrafts)
  {
    updraft
      .movedBy(-m_scrollPos)
      .draw(updraft.contains(m_player.pos) ? Palette::Deepskyblue : Palette::Skyblue);
  }

  for (const auto& line : m_lines)
  {
    line
      .movedBy(-m_scrollPos)
      .draw(Palette::Deeppink, 2);
  }

  m_player.draw();

  // const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;
  // const char *buf = Format("d: ", distance, ", walking: ", distance <= 0, ", v: ", m_player.speed);
  // m_font.draw(buf, m_player.pos.asPoint(), Palette::White);
  // delete[] buf;
}
