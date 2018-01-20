#include "Stage.hpp"

void Stage::update()
{
  player.update();
}

void Stage::draw() const
{
  player.draw();
}
