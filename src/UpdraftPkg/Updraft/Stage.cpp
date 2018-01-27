#include "Stage.hpp"

#include "Graphics/Screen.hpp"
#include "System/Input.hpp"
#include "System/Logger.hpp"
#include "Utils/Format.hpp"
#include "Utils/Utility.hpp"

Vec2 Stage::clampPlayerSpeed(const Vec2 speed)
{
  return {
    Clamp(speed.x, m_playerParams.minGlideSpeed.x, m_playerParams.maxGlideSpeed.x),
    Clamp(speed.y, m_playerParams.minGlideSpeed.y, m_playerParams.maxGlideSpeed.y)
  };
}

void Stage::processWalkingPlayerInput()
{
  m_player.speed = {0, 0};
  
  if (Input::KeyRight.pressed())
  {
    m_player.speed.x += m_playerParams.walkSpeed;
  }
  if (Input::KeyLeft.pressed())
  {
    m_player.speed.x -= m_playerParams.walkSpeed;
  }
  if (Input::KeySpace.pressed())
  {
    m_player.speed.y = m_playerParams.jumpSpeed;
  }
}

void Stage::processGlidingPlayerInput()
{
  if (Input::KeyRight.pressed())
  {
    m_player.speed.x += m_playerParams.glideAcceleration.x;
  }
  if (Input::KeyLeft.pressed())
  {
    m_player.speed.x -= m_playerParams.glideAcceleration.x;
  }

  m_player.speed.y += m_playerParams.glideAcceleration.y;

  m_player.speed = clampPlayerSpeed(m_player.speed);
}

void Stage::processCollision()
{
  const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;

  if (distance <= m_playerParams.walkSpeed)
  {
    const Vec2 normalizedVec = m_line.vector().normalized();
    const double angle = (m_line.begin.x < m_line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

    m_player.pos += normalizedVec.rotated(angle) * -distance;
  }
}

void Stage::movePlayer()
{
  const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;

  if (distance <= 0)
    processWalkingPlayerInput();
  else
    processGlidingPlayerInput();
  
  m_player.pos += m_player.speed;

  processCollision();
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

void Stage::update()
{
  movePlayer();

  if (!isPlayerInStage())
    killPlayer();
}

void Stage::draw() const
{
  const double distance = m_line.distanceFrom(m_player.pos) - m_player.r;

  m_line.draw(Palette::Deeppink);

  m_player.draw();

  const char *buf = Format("d: ", distance, ", walking: ", distance <= 0, ", v: ", m_player.speed);
  m_font.draw(buf, m_player.pos.asPoint(), Palette::White);
  delete[] buf;
}
