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

  Player m_player;

  Array<Line> m_lines;

  Array<Rect> m_updrafts;

  Vec2 clampPlayerSpeed(const Vec2 speed, const PlayerParams playerParams);

  void processWalkingPlayerInput(const PlayerParams playerParams);

  void processGlidingPlayerInput(const PlayerParams playerParams);

  void processCollision(const PlayerParams playerParams);

  void movePlayer(const PlayerParams playerParams);

  bool isPlayerInStage();

  void killPlayer();

public:
  Stage(const Vec2 stageSize)
    : m_font(L"Fonts\\Logger.fnt")
    , m_stageSize(stageSize)
    , m_playerInitialPos(400, 100)
    , m_player(m_playerInitialPos)
  { }

  Array<Line>& lines();

  const Array<Line>& lines() const;

  Array<Rect>& updrafts();

  const Array<Rect>& updrafts() const;

  void update(const PlayerParams playerParams);

  void draw() const;
};
