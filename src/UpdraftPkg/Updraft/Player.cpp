#include "Player.hpp"

#include "Graphics/Circle.hpp"
#include "Graphics/ColorPalette.hpp"

void Player::draw() const
{
  Circle(pos.asPoint(), 15).draw(Palette::Chocolate);
}
