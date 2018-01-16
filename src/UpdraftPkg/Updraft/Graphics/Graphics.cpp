#include "Graphics.hpp"

#include "../System/UefiSystem.hpp"
#include "../System/Logger.hpp"
#include "../System/Assert.hpp"
#include "Screen.hpp"

EFI_GRAPHICS_OUTPUT_PROTOCOL *Graphics::s_GraphicsOutputProtocol = nullptr;

EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Graphics::s_bltBuffer = nullptr;

Color Graphics::s_backgroundColor;

void Graphics::LocateGOP()
{
  const auto status =
    UefiSystem::SystemTable()->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, nullptr, (void **)&s_GraphicsOutputProtocol);
  AssertEfiStatus(status, "Failed to locate EFI Graphics Output Protocol.");
}

void Graphics::CheckPixelFormat()
{
  const auto pixelFormat = s_GraphicsOutputProtocol->Mode->Info->PixelFormat;
  Assert(pixelFormat == PixelRedGreenBlueReserved8BitPerColor || pixelFormat == PixelBlueGreenRedReserved8BitPerColor, "Not supported pixel format.");
}

bool Graphics::IsProperGraphicsMode(const EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo, const uint32 horizontalResolution, const uint32 verticalResolution)
{
  return (modeInfo->PixelFormat == PixelBlueGreenRedReserved8BitPerColor || modeInfo->PixelFormat == PixelRedGreenBlueReserved8BitPerColor) &&
    modeInfo->HorizontalResolution == horizontalResolution &&
    modeInfo->VerticalResolution == verticalResolution;
}

uint32 Graphics::GetProperGraphicsMode(const uint32 horizontalResolution, const uint32 verticalResolution)
{
  for(uint32 i = 0; i < s_GraphicsOutputProtocol->Mode->MaxMode; i++){
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *modeInfo;
    uintn sizeOfModeInfo;

    const auto status = s_GraphicsOutputProtocol->QueryMode(s_GraphicsOutputProtocol, i, &sizeOfModeInfo, &modeInfo);
    AssertEfiStatus(status, "Failed to query video mode.");

    if(IsProperGraphicsMode(modeInfo, horizontalResolution, verticalResolution))
    {
      return i;
    }
  }

  return 0;
}

void Graphics::SetVideoMode(const uint32 mode)
{
  const auto status = s_GraphicsOutputProtocol->SetMode(s_GraphicsOutputProtocol, mode);
  AssertEfiStatus(status, "Failed to set video mode.");

  Logger::ClearPrint();
}

void Graphics::AllocateBltBuffer()
{
  s_bltBuffer = new EFI_GRAPHICS_OUTPUT_BLT_PIXEL[Screen::Width() * Screen::Height()];
  AssertNotNullptr(s_bltBuffer, "Failed to allocate Blt buffer.");
}

void Graphics::ClearScreen()
{
  Screen::Rect().draw(s_backgroundColor);
}

void Graphics::Initialize(const Color backgroundColor)
{
  LocateGOP();

  CheckPixelFormat();

  SetVideoMode(GetProperGraphicsMode(800, 600));

  AllocateBltBuffer();

  s_backgroundColor = backgroundColor;
}

void Graphics::Update()
{
  const auto status = s_GraphicsOutputProtocol->Blt(s_GraphicsOutputProtocol, s_bltBuffer, ::EfiBltBufferToVideo, 0, 0, 0, 0, Screen::Width(), Screen::Height(), 0);
  AssertEfiStatus(status, "Block Transfer failed.");

  ClearScreen();
}

EFI_GRAPHICS_OUTPUT_PROTOCOL* Graphics::GraphicsOutputProtocol()
{
  return s_GraphicsOutputProtocol;
}

EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Graphics::BltBuffer()
{
  return s_bltBuffer;
}

void Graphics::BackgroundColor(const Color backgroundColor)
{
  s_backgroundColor = backgroundColor;
}

Color Graphics::BackgroundColor()
{
  return s_backgroundColor;
}
