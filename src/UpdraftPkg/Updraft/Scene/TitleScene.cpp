#include "TitleScene.hpp"

#include "SceneManager.hpp"
#include "PlayScene.hpp"
#include "../System/Input.hpp"
#include "../System/Lifecycle.hpp"
#include "../Graphics/Screen.hpp"
#include "../Graphics/Graphics.hpp"

TitleScene::TitleScene()
  : Scene()
  , font(L"Fonts\\MisakiGothic.fnt")
{ }

void TitleScene::drawBackground() const
{
  const int width = Screen::Width(),
            yStart = (int)Lifecycle::FrameCount() % 200,
            yEnd = (int)Screen::Height() + ((int)Lifecycle::FrameCount() % 200);
  int i = 0;

  for (int y = yStart; y < yEnd; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      if ((x % 200 < 100) != (y % 200 < 100))
        Graphics::PlotBltBuffer(i, Palette::Lightblue);
      else
        Graphics::PlotBltBuffer(i, Palette::Powderblue);
      i++;
    }
  }
}

void TitleScene::drawTitle() const
{
  const int delta = (Lifecycle::FrameCount() % 120 < 60)
    ? Lifecycle::FrameCount() % 60
    : 60 - Lifecycle::FrameCount() % 60;
  font.draw("Updraft", {215, 140 + delta - 30}, Palette::Salmon, 5);
}

void TitleScene::update()
{
  if (Input::Key1.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map1.ump"));
  }
  else if (Input::Key2.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map2.ump"));
  }
  else if (Input::Key3.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map3.ump"));
  }
  else if (Input::Key4.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map4.ump"));
  }
  else if (Input::Key5.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map5.ump"));
  }
  else if (Input::Key6.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map6.ump"));
  }
  else if (Input::Key7.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map7.ump"));
  }
  else if (Input::Key8.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map8.ump"));
  }
  else if (Input::Key9.pressed())
  {
    SceneManager::changeScene(new PlayScene(L"Map9.ump"));
  }
}

void TitleScene::draw() const
{
  drawBackground();
  drawTitle();

  if (Lifecycle::FrameCount() % 90 < 80)
    font.draw("PRESS [1] ~ [9] KEY TO START", {250, 430}, Palette::Darkslateblue);
}
