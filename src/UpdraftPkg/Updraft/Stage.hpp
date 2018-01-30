#pragma once

#include "Graphics/Font.hpp"
#include "Graphics/Line.hpp"
#include "Graphics/Rect.hpp"
#include "Player.hpp"

class Stage
{
  const Font m_font;

  const Vec2 m_stageSize;
  const Vec2 m_playerInitialPos;

  const PlayerParams m_playerParams;

  Player m_player;

  const Line m_line;

  const Rect m_updraft;

  Vec2 clampPlayerSpeed(const Vec2 speed);

  void processWalkingPlayerInput();

  void processGlidingPlayerInput();

  void processCollision();

  void movePlayer();

  bool isPlayerInStage();

  void killPlayer();

public:
  Stage(const PlayerParams playerParams)
    : m_font(L"Fonts\\Logger.fnt")
    , m_stageSize(800, 600)
    , m_playerInitialPos(400, 100)
    , m_playerParams(playerParams)
    , m_player(m_playerInitialPos)
    , m_line(200, 400, 600, 200)
    , m_updraft(50, 0, 100, 600)
  { }

  void update();

  void draw() const;
};
