#include "Assert.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"

void Assert(const bool value, const char *msg)
{
  if (!value)
  {
    Logger::Println_("Assertion error: ", msg);
    UefiSystem::SleepForever();
  }
}

void AssertEfiStatus(const EFI_STATUS status, const char *msg)
{
  if (EFI_ERROR(status))
  {
    Logger::Println_("Assertion error(", PrintEfiStatus(status), "): ", msg);
    UefiSystem::SleepForever();
  }
}
