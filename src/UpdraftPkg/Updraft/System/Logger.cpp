#include "Logger.hpp"

extern "C" {
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
}

#include <stdarg.h>

#include "UefiSystem.hpp"
#include "Lifecycle.hpp"
#include "Assert.hpp"
#include "../Graphics/ColorPalette.hpp"

const Font *Logger::s_font = nullptr;

char Logger::s_log[512];
uint16 Logger::s_caret = 0;

void Logger::PrintChar(const char ch)
{
  if (s_caret >= 512)
  {
    ClearPrint();
  }

  s_log[s_caret] = ch;
  s_caret++;
}

void Logger::PrintString(const char* str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    PrintChar(str[i]);
  }
}

void Logger::Initialize()
{
  s_font = new Font(L"Fonts\\Logger.fnt");

  for (int i = 0; i < 512; i++)
  {
    s_log[i] = '\0';
  }
}

void Logger::Update()
{
  AssertNotNullptr(s_font, "Logger::s_font is nullptr.");
  s_font->draw(s_log, {1, 1}, Palette::Black);
  s_font->draw(s_log, {0, 0}, Palette::White);
}

void Logger::Dispose()
{
  delete s_font;
}

void Logger::Print_()
{ }

void Logger::Print_(const int8 value)
{
  Printf("%d", value);
}

void Logger::Print_(const int16 value)
{
  Printf("%d", value);
}

void Logger::Print_(const int32 value)
{
  Printf("%d", value);
}

void Logger::Print_(const int64 value)
{
  Printf("%ld", value);
}

void Logger::Print_(const double value)
{
  Printf("%g", value);
}

void Logger::Print_(const uint8 value)
{
  Printf("%u", value);
}

void Logger::Print_(const uint16 value)
{
  Printf("%u", value);
}

void Logger::Print_(const uint32 value)
{
  Printf("%u", value);
}

void Logger::Print_(const uint64 value)
{
  Printf("%lu", value);
}

void Logger::Print_(const CHAR8 *value)
{
  Printf("%s", value);
}

void Logger::Print_(const CHAR16 *value)
{
  const uintn bufSize = ::StrLen(value);
  char *buf = new char[bufSize];
  ::UnicodeStrToAsciiStr(value, buf);

  Printf("%s", buf);
  
  delete[] buf;
}

void Logger::Print_(const bool value)
{
  Print_(value ? "true" : "false");
}

void Logger::Print_(const PrintEfiStatus value)
{
  switch(value.m_returnStatus)
  {
    case RETURN_SUCCESS:
      Print_("Success");
      break;
    case RETURN_LOAD_ERROR:
      Print_("Load Error");
      break;
    case RETURN_INVALID_PARAMETER:
      Print_("Invalid Parameter");
      break;
    case RETURN_UNSUPPORTED:
      Print_("Unsupported");
      break;
    case RETURN_BAD_BUFFER_SIZE:
      Print_("Bad Buffer Size");
      break;
    case RETURN_BUFFER_TOO_SMALL:
      Print_("Buffer Too Small");
      break;
    case RETURN_NOT_READY:
      Print_("Not Ready");
      break;
    case RETURN_DEVICE_ERROR:
      Print_("Device Error");
      break;
    case RETURN_WRITE_PROTECTED:
      Print_("Write Protected");
      break;
    case RETURN_OUT_OF_RESOURCES:
      Print_("Out of Resources");
      break;
    case RETURN_VOLUME_CORRUPTED:
      Print_("Volume Corrupt");
      break;
    case RETURN_VOLUME_FULL:
      Print_("Volume Full");
      break;
    case RETURN_NO_MEDIA:
      Print_("No Media");
      break;
    case RETURN_MEDIA_CHANGED:
      Print_("Media changed");
      break;
    case RETURN_NOT_FOUND:
      Print_("Not Found");
      break;
    case RETURN_ACCESS_DENIED:
      Print_("Access Denied");
      break;
    case RETURN_NO_RESPONSE:
      Print_("No Response");
      break;
    case RETURN_NO_MAPPING:
      Print_("No mapping");
      break;
    case RETURN_TIMEOUT:
      Print_("Time out");
      break;
    case RETURN_NOT_STARTED:
      Print_("Not started");
      break;
    case RETURN_ALREADY_STARTED:
      Print_("Already started");
      break;
    case RETURN_ABORTED:
      Print_("Aborted");
      break;
    case RETURN_ICMP_ERROR:
      Print_("ICMP Error");
      break;
    case RETURN_TFTP_ERROR:
      Print_("TFTP Error");
      break;
    case RETURN_PROTOCOL_ERROR:
      Print_("Protocol Error");
      break;
    case RETURN_WARN_UNKNOWN_GLYPH:
      Print_("Warning Unknown Glyph");
      break;
    case RETURN_WARN_DELETE_FAILURE:
      Print_("Warning Delete Failure");
      break;
    case RETURN_WARN_WRITE_FAILURE:
      Print_("Warning Write Failure");
      break;
    case RETURN_WARN_BUFFER_TOO_SMALL:
      Print_("Warning Buffer Too Small");
      break;
  }
}

void Logger::Print_(const Vec2 value)
{
  Print_("(", value.x, ",", value.y, ")");
}

void Logger::Print_(const Circular value)
{
  Print_("(", value.r, ",", value.theta, ")");
}

void Logger::Print_(const Circle value)
{
  Print_("(", value.center.x, ",", value.center.y, ",", value.r, ")");
}

void Logger::Print_(const Color value)
{
  Print_("(", value.r, ",", value.g, ",", value.b, ",", value.a, ")");
}

void Logger::Print_(const Point value)
{
  Print_("(", value.x, ",", value.y, ")");
}

void Logger::Print_(const Rect value)
{
  Print_("(", value.pos.x, ",", value.pos.y, ",", value.size.width, ",", value.size.height, ")");
}

void Logger::Print_(const Size value)
{
  Print_("(", value.width, ",", value.height, ")");
}

void Logger::ClearPrint()
{
  for (int i = 0; i < 512; i++)
  {
    s_log[i] = '\0';
  }
  s_caret = 0;
}
