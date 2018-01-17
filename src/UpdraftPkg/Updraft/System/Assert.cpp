#include "Assert.hpp"

extern "C" {
#include <Uefi.h>
#include <Library/UefiLib.h>
}

#include "UefiSystem.hpp"

void Assert(const bool value, const char *msg)
{
  if (!value)
  {
    ::Print((CHAR16 *)L"Assertion error: %a", msg);
    UefiSystem::SleepForever();
  }
}

void AssertEfiStatus(const EFI_STATUS status, const char *msg)
{
  if (EFI_ERROR(status))
  {
    ::Print((CHAR16 *)L"Assertion error(%r): %a", status, msg);
    UefiSystem::SleepForever();
  }
}
