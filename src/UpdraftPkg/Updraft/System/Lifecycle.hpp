extern "C" {
#include <Uefi.h>
}

#include "../Utils/Types.hpp"

class Lifecycle {
  static uint8 fps;

  static uint32 frameCount;

  static EFI_EVENT timerEvent;

  static EFI_EVENT eventList[1];

  static uintn eventIndex;

public:
  static void initialize();

  static bool update();

  static uint8 getFPS();

  static void setFPS(const uint8 _fps);

  static uint32 getFrameCount();
};
