extern "C" {
#include <Uefi.h>
}

#include "System/UefiSystem.hpp"
#include "System/Lifecycle.hpp"
#include "System/Mouse.hpp"
#include "System/Logger.hpp"
#include "Graphics/Graphics.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Circle.hpp"
#include "Graphics/Screen.hpp"
#include "Graphics/ColorPalette.hpp"

EFI_STATUS UefiMain(EFI_HANDLE, EFI_SYSTEM_TABLE *SystemTable)
{
  UefiSystem::Initialize(SystemTable);
  Graphics::Initialize();
  Lifecycle::Initialize();
  Mouse::Initialize();

  while(Lifecycle::Update())
  {
    Graphics::Update();
    Mouse::Update();

    Rect(300, 200, 120, 230).draw(Palette::Orange);
    Circle(Mouse::Pos(), 15).draw(Mouse::Pressed() ? Palette::Deeppink : Palette::Limegreen);
  }

  //return EFI_SUCCESS;
}

// Required to use LibC
int main() {}
