#pragma once

#include "Utils/Types.hpp"
#include "Utils/Vec2.hpp"
#include "Graphics/Line.hpp"

class Stage;

struct PlayerParams
{
  Vec2 glideAcceleration;
  Vec2 minGlideSpeed;
  Vec2 maxGlideSpeed;

  double walkSpeed;
  double jumpSpeed;
  double updraftAcceleration;
};

class Player
{
  Stage *m_stage;

  bool isGliding() const;

  bool isWalking() const;

  void clampSpeed(const PlayerParams playerParams);

  void jump(const PlayerParams playerParams);

  void processInput(const PlayerParams playerParams);

  void processCollision(const PlayerParams playerParams, const Vec2 oldPos);

public:
  const Vec2 initialPos;

  Vec2 pos;
  Vec2 speed = {0.0, 0.0};
  
  Line *walkingLine = nullptr;

  const uint8 r = 15;

  Player(const Vec2 _initialPos, Stage *stage)
    : initialPos(_initialPos)
    , pos(initialPos)
    , m_stage(stage)
  { }

  void update(const PlayerParams playerParams);

  void draw() const;

  void reset();
};
