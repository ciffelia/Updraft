#include "Screen.hpp"

#include "../UefiSystem.hpp"

Size Screen::size()
{
  return {width(), height()};
}

Point Screen::center()
{
  return {(int32)width() / 2, (int32)height() / 2};
}

Rect Screen::rect()
{
  return Rect({0, 0}, size());
}

uint32 Screen::width()
{
  return UefiSystem::getGraphicsOutputProtocol()->Mode->Info->HorizontalResolution;
}

uint32 Screen::height()
{
  return UefiSystem::getGraphicsOutputProtocol()->Mode->Info->VerticalResolution;
}
