#include "Graphics.hpp"

extern "C" {
#include <Library/MemoryAllocationLib.h>
}

#include "../System/UefiSystem.hpp"
#include "../System/Lifecycle.hpp"
#include "../System/Logger.hpp"
#include "Screen.hpp"

EFI_GRAPHICS_OUTPUT_PROTOCOL *Graphics::s_GraphicsOutputProtocol = nullptr;

EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Graphics::s_bltBuffer = nullptr;

Color Graphics::s_backgroundColor;

void Graphics::LocateGOP()
{
  const auto status =
    UefiSystem::SystemTable()->BootServices->LocateProtocol(&gEfiGraphicsOutputProtocolGuid, nullptr, (void **)&s_GraphicsOutputProtocol);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on locate EFI Graphics Output Protocol.");
    UefiSystem::SleepForever();
  }
}

void Graphics::CheckPixelFormat()
{
  const auto pixelFormat = s_GraphicsOutputProtocol->Mode->Info->PixelFormat;
  if(pixelFormat != PixelRedGreenBlueReserved8BitPerColor && pixelFormat != PixelBlueGreenRedReserved8BitPerColor)
  {
    Logger::Println_("Error: Not supported pixel format.");
    UefiSystem::SleepForever();
  }
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
    if(EFI_ERROR(status))
    {
      Logger::Println_("Error: ", status, " on query video mode.");
      UefiSystem::SleepForever();
    }
    else if(IsProperGraphicsMode(modeInfo, horizontalResolution, verticalResolution))
    {
      return i;
    }
  }

  return 0;
}

void Graphics::SetVideoMode(const uint32 mode)
{
  const auto status = s_GraphicsOutputProtocol->SetMode(s_GraphicsOutputProtocol, mode);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, " on set video mode.");
    UefiSystem::SleepForever();
  }

  Logger::ClearPrint();
}

void Graphics::AllocateBltBuffer()
{
  s_bltBuffer = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)AllocateZeroPool(Screen::Width() * Screen::Height() * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  if(s_bltBuffer == nullptr) {
    Logger::Println_("Error: Failed to allocate Blt buffer.");
    UefiSystem::SleepForever();
  }
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
  if (EFI_ERROR(status))
  {
    Logger::Println_("Error: ", status, "on Block Transfer.");
    UefiSystem::SleepForever();
  }

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
