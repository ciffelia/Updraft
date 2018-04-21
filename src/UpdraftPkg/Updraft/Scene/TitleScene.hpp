#pragma once

#include "SceneManager.hpp"
#include "../Graphics/Font.hpp"

class TitleScene : public Scene
{
  const Font font;

  void drawBackground() const;

  void drawTitle() const;

public:
  TitleScene();

  void update() override;

  void draw() const override;
};
