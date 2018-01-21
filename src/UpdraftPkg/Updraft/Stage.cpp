#include "Stage.hpp"

#include "Graphics/Screen.hpp"
#include "System/Mouse.hpp"
#include "Utils/Format.hpp"
#include "Utils/Utility.hpp"

Vec2 Stage::clampPlayerSpeed(const Vec2 speed)
{
  return {
    Clamp(speed.x, m_playerParams.minSpeed.x, m_playerParams.maxSpeed.x),
    Clamp(speed.y, m_playerParams.minSpeed.y, m_playerParams.maxSpeed.y)
  };
}

void Stage::processPlayerInput()
{
  m_player.speed.x += m_playerParams.acceleration.x * Mouse::Delta().x;
  m_player.speed.y += m_playerParams.acceleration.y;

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

  m_player.speed = clampPlayerSpeed(m_player.speed);

  Mouse::Pos(Screen::Center());
}

void Stage::movePlayer()
{
  processPlayerInput();

  m_player.pos += m_player.speed;
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
  m_player.draw();

  const char *buf = Format(m_player.pos);
  m_font.draw(buf, m_player.pos.asPoint(), Palette::White);
  delete[] buf;
}
