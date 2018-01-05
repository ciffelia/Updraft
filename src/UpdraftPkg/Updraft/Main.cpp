extern "C" {
#include <Uefi.h>
}

#include "System/UefiSystem.hpp"
#include "System/Lifecycle.hpp"
#include "System/Mouse.hpp"
#include "System/Logger.hpp"
#include "Graphics/Graphics.hpp"

EFI_STATUS UefiMain(EFI_HANDLE, EFI_SYSTEM_TABLE *SystemTable)
{
  UefiSystem::initialize(SystemTable);
  Lifecycle::initialize();
  Mouse::Initialize();
  Logger::Println_("Hello, UEFI World!");

  // Check screen resolution
  Logger::Println_("Screen resolution: ", Screen::size());

  // Graphics test
  Rect(300, 200, 120, 230).draw(Palette::Orange);
  Circle(200, 300, 125).draw(Palette::Skyblue);

  while(Lifecycle::update())
  {
    Circle(Mouse::Pos(), 8).draw(Palette::Black);

    Mouse::Update();

    Circle(Mouse::Pos(), 8).draw(Mouse::Pressed() ? Palette::Red : Palette::Orange);
  }

  //return EFI_SUCCESS;
}

// Required to use LibC
int main() {}
