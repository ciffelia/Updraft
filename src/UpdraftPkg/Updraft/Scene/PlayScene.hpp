#pragma once

#include "SceneManager.hpp"
#include "../Stage.hpp"

class PlayScene : public Scene
{
  Stage stage;

  const PlayerParams playerParams;

public:
  PlayScene(const wchar_t *fileName);

  void update() override;

  void draw() const override;
};
