#pragma once

#include "Graphics/Font.hpp"
#include "Player.hpp"

class Stage
{
  const Font m_font;

  const Vec2 m_stageSize = {800, 600};
  const Vec2 m_playerInitialPos = m_stageSize / 2;

  const PlayerParams m_playerParams;

  Player m_player;

  Vec2 clampPlayerSpeed(const Vec2 speed);

  void processPlayerInput();

  void movePlayer();

  bool isPlayerInStage();

  void killPlayer();

public:
  constexpr Stage(const PlayerParams playerParams)
    : m_font(L"Fonts\\Logger.fnt")
    , m_stageSize(800, 600)
    , m_playerInitialPos(m_stageSize / 2)
    , m_playerParams(playerParams)
    , m_player(m_playerInitialPos)
  { }

  void update();

  void draw() const;
};
