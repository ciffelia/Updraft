#pragma once

struct Scene
{
  virtual void update()
  { }

  virtual void draw() const
  { }
};

class SceneManager
{
  static Scene *scene;

public:
  static void update();

  static void draw();

  static void changeScene(Scene *newScene);
};
