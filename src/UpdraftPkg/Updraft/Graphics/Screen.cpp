#include "Screen.hpp"

#include "../Graphics/Graphics.hpp"

Point Screen::Center()
{
  return { (int32)Width() / 2, (int32)Height() / 2 };
}

uint32 Screen::Width()
{
  return Graphics::GraphicsOutputProtocol()->Mode->Info->HorizontalResolution;
}

uint32 Screen::Height()
{
  return Graphics::GraphicsOutputProtocol()->Mode->Info->VerticalResolution;
}
