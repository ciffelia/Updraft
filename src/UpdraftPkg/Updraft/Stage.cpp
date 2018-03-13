#include "Stage.hpp"

#include <float.h>

#include "Graphics/Screen.hpp"
#include "System/Input.hpp"
#include "System/Logger.hpp"
#include "Utils/Format.hpp"
#include "Utils/Utility.hpp"

Vec2 Stage::clampPlayerSpeed(const Vec2 speed, const PlayerParams playerParams)
{
  return {
    Clamp(speed.x, playerParams.minGlideSpeed.x, playerParams.maxGlideSpeed.x),
    Clamp(speed.y, playerParams.minGlideSpeed.y, playerParams.maxGlideSpeed.y)
  };
}

void Stage::processWalkingPlayerInput(const PlayerParams playerParams)
{
  m_player.speed = {0, 0};
  
  if (Input::KeyRight.pressed())
  {
    m_player.speed.x += playerParams.walkSpeed;
  }
  if (Input::KeyLeft.pressed())
  {
    m_player.speed.x -= playerParams.walkSpeed;
  }
  if (Input::KeySpace.pressed())
  {
    m_player.speed.y = playerParams.jumpSpeed;
  }
}

void Stage::processGlidingPlayerInput(const PlayerParams playerParams)
{
  if (Input::KeyRight.pressed())
  {
    m_player.speed.x += playerParams.glideAcceleration.x;
  }
  if (Input::KeyLeft.pressed())
  {
    m_player.speed.x -= playerParams.glideAcceleration.x;
  }

  m_player.speed.y += playerParams.glideAcceleration.y;

  for (const auto& updraft : m_updrafts)
  {
    if (updraft.contains(m_player.pos))
      m_player.speed.y += playerParams.updraftAcceleration;
  }

  m_player.speed = clampPlayerSpeed(m_player.speed, playerParams);
}

void Stage::processCollision(const PlayerParams playerParams)
{
  for (const auto& line : m_lines)
  {
    const double distance = line.distanceFrom(m_player.pos) - m_player.r;

    if (distance <= playerParams.walkSpeed)
    {
      const Vec2 normalizedVec = line.vector().normalized();
      const double angle = (line.begin.x < line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

      m_player.pos += normalizedVec.rotated(angle) * -distance;
    }
  }
}

void Stage::movePlayer(const PlayerParams playerParams)
{
  double minDistance = DBL_MAX;

  for (const auto& line : m_lines)
  {
    minDistance = Min(minDistance, line.distanceFrom(m_player.pos) - m_player.r);
  }

  if (minDistance <= 0)
    processWalkingPlayerInput(playerParams);
  else
    processGlidingPlayerInput(playerParams);

  m_player.pos += m_player.speed;

  processCollision(playerParams);
}

bool Stage::isPlayerInStage()
{
  return 0 < m_player.pos.x &&
         m_player.pos.x < m_stageSize.x &&
         0 < m_player.pos.y &&
         m_player.pos.y < m_stageSize.y;
}

void Stage::killPlayer()
{
  m_player.pos = m_playerInitialPos;
  m_player.speed = {0.0, 0.0};
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

void Stage::update(const PlayerParams playerParams)
{
  movePlayer(playerParams);

  if (!isPlayerInStage())
    killPlayer();
}

void Stage::draw() const
{
  for (const auto& updraft : m_updrafts)
  {
    updraft.draw(updraft.contains(m_player.pos) ? Palette::Deepskyblue : Palette::Skyblue);
  }

  for (const auto& line : m_lines)
  {
    line.draw(Palette::Deeppink);
  }

  m_player.draw();

  // const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;
  // const char *buf = Format("d: ", distance, ", walking: ", distance <= 0, ", v: ", m_player.speed);
  // m_font.draw(buf, m_player.pos.asPoint(), Palette::White);
  // delete[] buf;
}
