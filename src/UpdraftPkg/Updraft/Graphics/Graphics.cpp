#include "Graphics.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"

EFI_GRAPHICS_OUTPUT_PROTOCOL *Graphics::s_GraphicsOutputProtocol = nullptr;

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

void Graphics::Initialize()
{
  LocateGOP();

  CheckPixelFormat();

  SetVideoMode(GetProperGraphicsMode(800, 600));
}

EFI_GRAPHICS_OUTPUT_PROTOCOL* Graphics::GraphicsOutputProtocol()
{
  return s_GraphicsOutputProtocol;
}
