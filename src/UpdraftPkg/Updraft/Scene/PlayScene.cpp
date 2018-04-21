#include "PlayScene.hpp"

#include "../StageReader.hpp"

PlayScene::PlayScene(const wchar_t *fileName)
  : Scene()
  , stage(StageReader(fileName).read())
  , playerParams({
    {0.15, 0.3}, {-9.0, -7.5}, {9.0, 4.5},
    4.5,
    -7.5,
    -0.6
  })
{ }

void PlayScene::update()
{
  stage.update(playerParams);
}

void PlayScene::draw() const
{
  stage.draw();
}
