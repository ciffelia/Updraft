#include "Player.hpp"

#include "System/Input.hpp"
#include "Utils/Utility.hpp"
#include "Graphics/Circle.hpp"
#include "Graphics/ColorPalette.hpp"
#include "Graphics/Screen.hpp"
#include "Stage.hpp"

bool Player::isGliding() const
{
  return walkingLine == nullptr;
}

bool Player::isWalking() const
{
  return !isGliding();
}

void Player::clampSpeed(const PlayerParams playerParams)
{
  if (isGliding())
  {
    speed.x = Clamp(speed.x, playerParams.minGlideSpeed.x, playerParams.maxGlideSpeed.x);
    speed.y = Clamp(speed.y, playerParams.minGlideSpeed.y, playerParams.maxGlideSpeed.y);
  }
}

void Player::clampPos()
{
  if (pos.x - r < 0)
  {
    speed.x = 0;
    pos.x = r;
  }
  if (pos.y - r < 0)
  {
    speed.y = 0;
    pos.y = r;
  }
  if (pos.x + r > m_stage->size().x)
  {
    speed.x = 0;
    pos.x = m_stage->size().x - r;
  }
}

void Player::jump(const PlayerParams playerParams)
{
  speed.y = playerParams.jumpSpeed;
}

void Player::processInput(const PlayerParams playerParams)
{
  if (isWalking())
  {
    speed = {0, 0};

    if (Input::KeyRight.pressed())
    {
      speed.x += playerParams.walkSpeed;
    }
    if (Input::KeyLeft.pressed())
    {
      speed.x -= playerParams.walkSpeed;
    }
    if (Input::KeySpace.pressed() || Input::KeyUp.pressed())
    {
      walkingLine = nullptr;
      jump(playerParams);
    }
  }
  else
  {
    if (Input::KeyRight.pressed())
    {
      speed.x += playerParams.glideAcceleration.x;
    }
    if (Input::KeyLeft.pressed())
    {
      speed.x -= playerParams.glideAcceleration.x;
    }

    speed.y += playerParams.glideAcceleration.y;
  }
}

void Player::processCollision(const PlayerParams playerParams, const Vec2 oldPos)
{
  if (isWalking())
  {
    const Line line = *walkingLine;

    if ((pos - line.begin).dot(line.vector()) <= 0 || (pos - line.end).dot(line.vector()) >= 0)
    {
      walkingLine = nullptr;
      return;
    }

    const double distance = line.distanceFrom(pos) - r;

    if (distance <= playerParams.walkSpeed)
    {
      const Vec2 normalizedVec = line.vector().normalized();
      const double angle = (line.begin.x < line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

      pos += normalizedVec.rotated(angle) * -distance;
    }
  }
  else
  {
    for (auto &line : m_stage->lines())
    {
      const double oldDistance = line.distanceFrom(oldPos) - r;
      const double distance = line.distanceFrom(pos) - r;

      if (oldDistance > 0 && distance <= 0 && speed.y >= 0)
      {
        const Vec2 normalizedVec = line.vector().normalized();
        const double angle = (line.begin.x < line.end.x) ? Math::Pi * 3 / 2 : Math::Pi / 2;

        pos += normalizedVec.rotated(angle) * -distance;
        walkingLine = &line;
      }
    }
  }
}

void Player::scrollStage() const
{
  const Point screenSize(Screen::Width(), Screen::Height());
  const Point posPoint = pos.asPoint();

  const Point diff = m_stage->scrollPos() + screenSize / 2 - posPoint;

  if (diff.x < -30)
    m_stage->scrollPos().x = posPoint.x - screenSize.x / 2 - 30;
  if (diff.x > 30)
    m_stage->scrollPos().x = posPoint.x - screenSize.x / 2 + 30;
  if (diff.y < -30)
    m_stage->scrollPos().y = posPoint.y - screenSize.y / 2 - 30;
  if (diff.y > 30)
    m_stage->scrollPos().y = posPoint.y - screenSize.y / 2 + 30;

  if (m_stage->scrollPos().x < 0)
    m_stage->scrollPos().x = 0;
  if (m_stage->scrollPos().y < 0)
    m_stage->scrollPos().y = 0;
  if (m_stage->scrollPos().x > m_stage->size().x - screenSize.x)
    m_stage->scrollPos().x = m_stage->size().x - screenSize.x;
  if (m_stage->scrollPos().y > m_stage->size().y - screenSize.y)
    m_stage->scrollPos().y = m_stage->size().y - screenSize.y;
}

void Player::reset()
{
  pos = initialPos;
  speed = {0.0, 0.0};
}

void Player::update(const PlayerParams playerParams)
{
  processInput(playerParams);

  if (isGliding() && m_stage->isInUpdraft(pos))
    speed.y += playerParams.updraftAcceleration;

  if (isGliding())
    clampSpeed(playerParams);

  const auto oldPos = pos;
  pos += speed;

  processCollision(playerParams, oldPos);

  clampPos();

  if (pos.y > m_stage->size().y)
    reset();

  scrollStage();
}

void Player::draw() const
{
  Circle(pos.asPoint(), r)
    .movedBy(-m_stage->scrollPos())
    .draw(Palette::Chocolate);
}
