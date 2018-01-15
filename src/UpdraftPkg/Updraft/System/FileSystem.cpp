#include "FileSystem.hpp"

extern "C" {
#include <Guid/FileInfo.h>
}

#include "UefiSystem.hpp"
#include "Logger.hpp"

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem::s_SimpleFileSystemProtocol;

EFI_FILE_PROTOCOL *FileSystem::s_root;

void FileSystem::LocateSimpleFileSystemProtocol()
{
  const auto status =
    UefiSystem::SystemTable()->BootServices->LocateProtocol(&gEfiSimpleFileSystemProtocolGuid, nullptr, (void **)&s_SimpleFileSystemProtocol);
  if (EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on locate EFI Simple File System Protocol.");
    UefiSystem::SleepForever();
  }
}

void FileSystem::OpenVolume()
{
  const auto status = s_SimpleFileSystemProtocol->OpenVolume(s_SimpleFileSystemProtocol, &s_root);
  if (EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on open volume.");
    UefiSystem::SleepForever();
  }
}

void FileSystem::OpenFile(CHAR16 *fileName, EFI_FILE_PROTOCOL **file)
{
  const auto status = s_root->Open(s_root, file, fileName, EFI_FILE_MODE_READ, 0);
  if (EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on open file.");
    UefiSystem::SleepForever();
  }
}

void FileSystem::CloseFile(EFI_FILE_PROTOCOL *file)
{
  s_root->Close(file);
}

void FileSystem::Initialize()
{
  LocateSimpleFileSystemProtocol();
  OpenVolume();
}

uint64 FileSystem::GetSize(CHAR16 *fileName)
{
  EFI_FILE_PROTOCOL *file;
  OpenFile(fileName, &file);

  uint8 buf[1024];
  uintn bufSize = 1024;
  const auto status = file->GetInfo(file, &gEfiFileInfoGuid, &bufSize, (void *)buf);
  if (EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on get file size.");
    UefiSystem::SleepForever();
  }

  CloseFile(file);

  return ((EFI_FILE_INFO *)buf)->FileSize;
}

void FileSystem::Read(CHAR16 *fileName, uintn *bufSize, void *buf)
{
  EFI_FILE_PROTOCOL *file;
  OpenFile(fileName, &file);

  const auto status = file->Read(file, bufSize, buf);
  if (EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on read file.");
    UefiSystem::SleepForever();
  }

  CloseFile(file);
}
