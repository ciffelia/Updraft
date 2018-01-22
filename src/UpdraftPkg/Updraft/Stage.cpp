#include "Stage.hpp"

#include "Graphics/Screen.hpp"
#include "System/Mouse.hpp"
#include "Utils/Format.hpp"
#include "Utils/Utility.hpp"

Vec2 Stage::clampPlayerSpeed(const Vec2 speed)
{
  if (m_line.distanceFrom(m_player.pos) <= m_player.r)
  {
    return {
      Clamp(speed.x, -m_playerParams.walkSpeed, m_playerParams.walkSpeed),
      speed.y
    };
  }
  
  return {
    Clamp(speed.x, -m_playerParams.maxSlideSpeed, m_playerParams.maxSlideSpeed),
    Max(speed.y, m_playerParams.maxFallSpeed)
  };
}

void Stage::processPlayerInput()
{
  if (Mouse::RightPressed())
  {
    m_player.speed.x += m_playerParams.acceleration.x;
  }
  if (Mouse::LeftPressed())
  {
    m_player.speed.x -= m_playerParams.acceleration.x;
  }
  if (!Mouse::RightPressed() && !Mouse::LeftPressed())
  {
    if (m_player.speed.x > 0)
    {
      m_player.speed.x -= m_playerParams.acceleration.x;
      m_player.speed.x = Max(0.0, m_player.speed.x);
    }
    else if (m_player.speed.x < 0)
    {
      m_player.speed.x += m_playerParams.acceleration.x;
      m_player.speed.x = Min(0.0, m_player.speed.x);
    }
  }

  if (m_line.distanceFrom(m_player.pos) <= m_player.r)
  {
    m_player.speed.y = 0;
  }
  else
  {
    m_player.speed.y += m_playerParams.acceleration.y;
  }

  m_player.speed = clampPlayerSpeed(m_player.speed);
}

void Stage::processCollision()
{
  const double distance = m_line.distanceFrom(m_player.pos);
  if (distance <= m_player.r)
  {
    const Vec2 normalizedVec = m_line.vector().normalized();
    const double angle = (m_line.begin.x < m_line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

    m_player.pos += normalizedVec.rotated(angle) * (m_player.r - distance);
  }
}

void Stage::movePlayer()
{
  processPlayerInput();

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
  m_line.draw(Palette::Deeppink);

  m_player.draw();
}
