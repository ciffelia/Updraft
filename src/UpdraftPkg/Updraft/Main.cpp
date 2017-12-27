extern "C" {
#include <Uefi.h>
}

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Graphics/Graphics.hpp"

EFI_STATUS UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
  UefiSystem::initialize(SystemTable);
  Logger::Println_("Hello, UEFI World!");

  // Check screen resolution
  Logger::Println_("Screen resolution: ", Screen::size());

  // Graphics test
  Rect(300, 200, 120, 230).draw(Palette::Orange);
  Circle(200, 300, 125).draw(Palette::Skyblue);

  UefiSystem::loopForever();

  //return EFI_SUCCESS;
}

// Required to use LibC
int main() {}
