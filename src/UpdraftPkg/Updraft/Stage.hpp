#pragma once

#include "Graphics/Screen.hpp"
#include "Player.hpp"

class Stage
{
  Player player;

public:
  constexpr Stage(const PlayerParams playerParams)
    : player(Screen::Center(), playerParams)
  { }

  void update();

  void draw() const;
};
