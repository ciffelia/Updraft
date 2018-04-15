extern "C" {
#include <Uefi.h>
}

#include "System/UefiSystem.hpp"
#include "System/Lifecycle.hpp"
#include "System/Logger.hpp"
#include "System/FileSystem.hpp"
#include "System/Input.hpp"
#include "Utils/Vec2.hpp"
#include "Utils/Circular.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Circle.hpp"
#include "Graphics/Screen.hpp"
#include "Graphics/ColorPalette.hpp"
#include "Graphics/Font.hpp"
#include "Stage.hpp"
#include "StageReader.hpp"

EFI_STATUS UefiMain(EFI_HANDLE, EFI_SYSTEM_TABLE *SystemTable)
{
  UefiSystem::Initialize(SystemTable);
  Graphics::Initialize();
  Lifecycle::Initialize();
  FileSystem::Initialize();
  Logger::Initialize();
  UsbKeyboard::Initialize();

  Stage stage = StageReader(L"Map2.ump").read();

  const PlayerParams playerParams = {
    {0.15, 0.3}, {-9.0, -7.5}, {9.0, 4.5},
    4.5,
    -7.5,
    -0.6
  };

  while (Lifecycle::Update())
  {
    stage.update(playerParams);
    stage.draw();

    const Vec2 circularPos = Vec2(200, 200) + Circular(100, Math::TwoPi * Lifecycle::FrameCount() / 180);
    Circle(circularPos.asPoint(), 15).draw(Palette::Orange);

    Logger::Update();

    Graphics::Update();
  }

  Logger::Dispose();
  Graphics::Dispose();

  UefiSystem::Shutdown();

  return EFI_SUCCESS;
}
