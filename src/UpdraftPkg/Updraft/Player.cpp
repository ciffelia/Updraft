#include "Player.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/ColorPalette.hpp"

void Player::draw() const
{
  Circle(pos.asPoint(), r).draw(Palette::Chocolate);
}
