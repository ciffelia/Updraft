extern "C" {
#include <Uefi.h>
#include <Protocol/SimpleTextIn.h>
}

#include "../Utils/Types.hpp"

class Lifecycle
{
  static EFI_SIMPLE_TEXT_INPUT_PROTOCOL *s_SimpleTextInputProtocol;

  static uint8 s_fps;

  static uint32 s_frameCount;

  static EFI_EVENT s_timerEvent;

  static EFI_EVENT s_eventList[1];

  static uintn s_eventIndex;

  static void LocateSimpleTextInputProtocol();

  static void ResetInputDevice();

  static bool ExitKeyPressed();

  static void ResetTimer();

public:
  static void Initialize();

  static bool Update();

  static uint8 FPS();

  static void FPS(const uint8 _fps);

  static uint32 FrameCount();
};
