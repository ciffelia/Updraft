#include "Stage.hpp"

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

  if (m_updraft.contains(m_player.pos))
    m_player.speed.y += playerParams.updraftAcceleration;

  m_player.speed = clampPlayerSpeed(m_player.speed, playerParams);
}

void Stage::processCollision(const PlayerParams playerParams)
{
  const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;

  if (distance <= playerParams.walkSpeed)
  {
    const Vec2 normalizedVec = m_line.vector().normalized();
    const double angle = (m_line.begin.x < m_line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

    m_player.pos += normalizedVec.rotated(angle) * -distance;
  }
}

void Stage::movePlayer(const PlayerParams playerParams)
{
  const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;

  if (distance <= 0)
    processWalkingPlayerInput(playerParams);
  else
    processGlidingPlayerInput(playerParams);
  
  m_player.pos += m_player.speed;

  processCollision(playerParams);
}

bool Stage::isPlayerInStage()
{
  return 0 < m_player.pos.x &&
         m_player.pos.x < m_stageSize.x * m_gridSize &&
         0 < m_player.pos.y &&
         m_player.pos.y < m_stageSize.y * m_gridSize;
}

void Stage::killPlayer()
{
  m_player.pos = m_playerInitialPos;
  m_player.speed = {0.0, 0.0};
}

void Stage::update(const PlayerParams playerParams)
{
  movePlayer(playerParams);

  if (!isPlayerInStage())
    killPlayer();
}

void Stage::draw() const
{
  m_updraft.draw(m_updraft.contains(m_player.pos) ? Palette::Deepskyblue : Palette::Skyblue);

  m_line.draw(Palette::Deeppink);

  m_player.draw();

  // const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;
  // const char *buf = Format("d: ", distance, ", walking: ", distance <= 0, ", v: ", m_player.speed);
  // m_font.draw(buf, m_player.pos.asPoint(), Palette::White);
  // delete[] buf;
}
