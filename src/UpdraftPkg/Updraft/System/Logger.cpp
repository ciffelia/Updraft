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

void Logger::ClearPrint()
{
  for (int i = 0; i < 512; i++)
  {
    s_log[i] = '\0';
  }
  s_caret = 0;
}
