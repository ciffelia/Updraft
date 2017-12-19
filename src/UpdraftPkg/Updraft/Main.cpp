extern "C" {
#include <Uefi.h>
}

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Graphics/Graphics.hpp"

EFI_STATUS UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  UefiSystem::initialize(SystemTable);

  // Check screen resolution
  Logger::Println_("Screen resolution: ", Screen::size());

  // Graphics test
  constexpr Rect rect(200, 300, 123, 321);
  constexpr Color color = Palette::Orange;
  Logger::Println_("Draw a rectangle! ", rect, " Color: ", color);
  rect.draw(color);

  UefiSystem::loop_forever();

  //return EFI_SUCCESS;
}

// Required to use LibC
int main() {}
