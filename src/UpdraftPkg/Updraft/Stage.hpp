#pragma once

#include "Graphics/Font.hpp"
#include "Graphics/Line.hpp"
#include "Graphics/Rect.hpp"
#include "Player.hpp"

class Stage
{
  const Font m_font;

  const uint16 m_gridSize;
  const Point m_stageSize;

  const uint16 m_lineSize;
  const uint16 m_updraftSize;

  const Vec2 m_playerInitialPos;

  Player m_player;

  const Line m_line;

  const Rect m_updraft;

  Vec2 clampPlayerSpeed(const Vec2 speed, const PlayerParams playerParams);

  void processWalkingPlayerInput(const PlayerParams playerParams);

  void processGlidingPlayerInput(const PlayerParams playerParams);

  void processCollision(const PlayerParams playerParams);

  void movePlayer(const PlayerParams playerParams);

  bool isPlayerInStage();

  void killPlayer();

public:
  Stage(const uint16 gridSize, const Point stageSize, const uint16 lineSize, const uint16 updraftSize)
    : m_font(L"Fonts\\Logger.fnt")
    , m_gridSize(gridSize)
    , m_stageSize(stageSize)
    , m_lineSize(lineSize)
    , m_updraftSize(updraftSize)
    , m_playerInitialPos(400, 100)
    , m_player(m_playerInitialPos)
    , m_line(200, 400, 600, 200)
    , m_updraft(50, 0, 100, 600)
  { }

  void update(const PlayerParams playerParams);

  void draw() const;
};
