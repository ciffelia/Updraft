#include "Logger.hpp"

extern "C" {
#include <Uefi.h>
#include <Library/UefiLib.h>
}
#include <stdio.h>

#include "UefiSystem.hpp"

void Logger::Print_()
{ }

void Logger::Print_(const CHAR8 value)
{
  ::Print((CHAR16*)u"%c", (CHAR16)value);
}

// void Logger::Print_(const CHAR16 value)
// {
//   ::Print((CHAR16*)u"%c", value);
// }

void Logger::Print_(const int8 value)
{
  ::Print((CHAR16*)u"%d", value);
}

void Logger::Print_(const int16 value)
{
  ::Print((CHAR16*)u"%d", value);
}

void Logger::Print_(const int32 value)
{
  ::Print((CHAR16*)u"%d", value);
}

void Logger::Print_(const int64 value)
{
  ::Print((CHAR16*)u"%Ld", value);
}

void Logger::Print_(const double value)
{
  char buf[64];
  sprintf(buf, "%f", value);
  ::Print((CHAR16*)u"%a", buf);
}

void Logger::Print_(const uint8 value)
{
  ::Print((CHAR16*)u"%u", value);
}

void Logger::Print_(const uint16 value)
{
  ::Print((CHAR16*)u"%u", value);
}

void Logger::Print_(const uint32 value)
{
  ::Print((CHAR16*)u"%u", value);
}

void Logger::Print_(const uint64 value)
{
  ::Print((CHAR16*)u"%Lu", value);
}

void Logger::Print_(const void *value)
{
  ::Print((CHAR16*)u"%p", value);
}

void Logger::Print_(const CHAR8 *value)
{
  ::Print((CHAR16*)u"%a", value);
}

void Logger::Print_(const CHAR16 *value)
{
  ::Print((CHAR16*)u"%s", value);
}

void Logger::Print_(const GUID *value)
{
  ::Print((CHAR16*)u"%g", value);
}

void Logger::Print_(const EFI_TIME *value)
{
  ::Print((CHAR16*)u"%s", value);
}

// void Logger::Print_(const RETURN_STATUS value)
// {
//   ::Print((CHAR16*)u"%r", value);
// }

void Logger::Print_(const Color value)
{
  Print_('(', value.r, ',', value.g, ',', value.b, ')');
}

void Logger::Print_(const Point value)
{
  Print_('(', value.x, ',', value.y, ')');
}

void Logger::Print_(const Rect value)
{
  Print_('(', value.pos.x, ',', value.pos.y, ',', value.size.width, ',', value.size.height, ')');
}

void Logger::Print_(const Size value)
{
  Print_('(', value.width, ',', value.height, ')');
}

void Logger::ClearPrint()
{
  UefiSystem::SystemTable->ConOut->ClearScreen(UefiSystem::SystemTable->ConOut);
}
