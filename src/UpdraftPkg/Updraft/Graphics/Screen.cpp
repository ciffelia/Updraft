#include "Screen.hpp"

#include "../Graphics/Graphics.hpp"

Size Screen::Size()
{
  return { Width(), Height() };
}

Point Screen::Center()
{
  return { (int32)Width() / 2, (int32)Height() / 2 };
}

Rect Screen::Rect()
{
  return Rect::Rect({0, 0}, Size());
}

uint32 Screen::Width()
{
  return Graphics::GraphicsOutputProtocol()->Mode->Info->HorizontalResolution;
}

uint32 Screen::Height()
{
  return Graphics::GraphicsOutputProtocol()->Mode->Info->VerticalResolution;
}
