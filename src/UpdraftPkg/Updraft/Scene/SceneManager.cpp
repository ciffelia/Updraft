#include "SceneManager.hpp"

Scene *SceneManager::scene = nullptr;

void SceneManager::update()
{
  scene->update();
}

void SceneManager::draw()
{
  scene->draw();
}

void SceneManager::changeScene(Scene *newScene)
{
  delete scene;
  scene = newScene;
}
