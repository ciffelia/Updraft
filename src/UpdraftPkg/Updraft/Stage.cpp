#include "Stage.hpp"

#include "Utils/Format.hpp"
#include "Utils/Utility.hpp"
#include "Graphics/Screen.hpp"
#include "Graphics/Graphics.hpp"
#include "Utils/Utility.hpp"
#include "Scene/SceneManager.hpp"
#include "Scene/TitleScene.hpp"

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
  if (m_goalCount == -1)
  {
    m_player.update(playerParams);

    if (m_player.pos.distanceFrom(m_goal.center) < m_goal.r + m_player.r)
      m_goalCount = 0;
  }
  else
  {
    m_goalCount++;

    if (m_goalCount >= 120)
      SceneManager::changeScene(new TitleScene());
  }
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

  m_goal
    .movedBy(-m_scrollPos)
    .draw(Palette::Lightcyan);
  m_font.draw("G", m_goal.center - Point(12, 17) - m_scrollPos, {20, 20, 20}, 2);

  if (m_goalCount != -1)
    m_font.draw("STAGE CLEAR", {80, 140}, Color(Palette::Indigo, Min(255, m_goalCount * 4)), 5);

  // const char *buf = Format(m_player.pos);
  // m_font.draw(buf, { 0, 0 }, Palette::White, 2);
  // delete[] buf;
}
