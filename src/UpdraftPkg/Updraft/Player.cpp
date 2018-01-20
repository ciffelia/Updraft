#include "Player.hpp"

#include "Utils/Utility.hpp"
#include "System/Mouse.hpp"
#include "Graphics/Screen.hpp"
#include "Graphics/Circle.hpp"
#include "Graphics/ColorPalette.hpp"

Vec2 Player::clampSpeed(const Vec2 speed) const
{
  return {
    Clamp(speed.x, m_minSpeed.x, m_maxSpeed.x),
    Clamp(speed.y, m_minSpeed.y, m_maxSpeed.y)
  };
}

void Player::updateSpeed()
{
  m_speed.x += m_acceleration.x * Mouse::Delta().x;
  m_speed.y += m_acceleration.y;

  if (m_speed.x > 0)
  {
    m_speed.x -= m_acceleration.x;
    m_speed.x = Max(0.0, m_speed.x);
  }
  else if (m_speed.x < 0)
  {
    m_speed.x += m_acceleration.x;
    m_speed.x = Min(0.0, m_speed.x);
  }

  m_speed = clampSpeed(m_speed);
}

void Player::update()
{
  updateSpeed();

  m_pos += m_speed;

  if (m_pos.y > Screen::Height())
    kill();

  Mouse::Pos(Screen::Center());
}

void Player::draw() const
{
  Circle(m_pos.asPoint(), 15).draw(Palette::Chocolate);
}

void Player::kill()
{
  m_pos = m_initialPos;
  m_speed = {0.0, 0.0};
}
