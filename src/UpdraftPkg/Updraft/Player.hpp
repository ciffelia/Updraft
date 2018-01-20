#pragma once

#include "Utils/Vec2.hpp"

struct PlayerParams
{
  Vec2 acceleration;
  Vec2 maxSpeed;
  Vec2 minSpeed;
};

class Player
{
  const Vec2 m_initialPos;
  const Vec2 m_acceleration;
  const Vec2 m_maxSpeed;
  const Vec2 m_minSpeed;

  Vec2 m_pos;
  Vec2 m_speed = {0.0, 0.0};

  Vec2 clampSpeed(const Vec2 speed) const;

  void updateSpeed();

public:
  constexpr Player(const Vec2 pos, const PlayerParams playerParams)
    : m_initialPos(pos)
    , m_acceleration(playerParams.acceleration)
    , m_maxSpeed(playerParams.maxSpeed)
    , m_minSpeed(playerParams.minSpeed)
    , m_pos(pos)
  { }

  void update();

  void draw() const;

  void kill();
};
