extern "C" {
#include <Uefi.h>
}

#include "System/UefiSystem.hpp"
#include "System/Lifecycle.hpp"
#include "System/Mouse.hpp"
#include "System/Logger.hpp"
#include "System/FileSystem.hpp"
#include "Utils/Vec2.hpp"
#include "Utils/Circular.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Circle.hpp"
#include "Graphics/Screen.hpp"
#include "Graphics/ColorPalette.hpp"
#include "Graphics/Font.hpp"

EFI_STATUS UefiMain(EFI_HANDLE, EFI_SYSTEM_TABLE *SystemTable)
{
  UefiSystem::Initialize(SystemTable);
  Graphics::Initialize();
  Lifecycle::Initialize();
  Mouse::Initialize();
  FileSystem::Initialize();
  Logger::Initialize();

  const Font font(L"Font.dat");

  while(Lifecycle::Update())
  {
    Mouse::Update();

    const Vec2 circularPos = Vec2(200, 200) + Circular(100, Math::TwoPi * Lifecycle::FrameCount() / 180);
    Circle(circularPos.asPoint(), 15).draw(Palette::Orange);

    Circle(Mouse::Pos(), 15).draw(Mouse::Pressed() ? Palette::Deeppink : Palette::Limegreen);

    font.draw(Mouse::Pressed() ? "Hello,\r\nworld!" : "Hello, world!", Mouse::Pos());

    Logger::Update();

    Graphics::Update();
  }

  //return EFI_SUCCESS;
}
