#include "FileSystem.hpp"

extern "C" {
#include <Guid/FileInfo.h>
}

#include "UefiSystem.hpp"
#include "Assert.hpp"

EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem::s_SimpleFileSystemProtocol = nullptr;

EFI_FILE_PROTOCOL *FileSystem::s_root = nullptr;

void FileSystem::LocateSimpleFileSystemProtocol()
{
  const auto status =
    UefiSystem::SystemTable()->BootServices->LocateProtocol(&gEfiSimpleFileSystemProtocolGuid, nullptr, (void **)&s_SimpleFileSystemProtocol);
  AssertEfiStatus(status, "Failed to locate EFI Simple File System Protocol.");
}

void FileSystem::OpenVolume()
{
  const auto status = s_SimpleFileSystemProtocol->OpenVolume(s_SimpleFileSystemProtocol, &s_root);
  AssertEfiStatus(status, "Failed to open volume.");
}

void FileSystem::OpenFile(wchar_t *fileName, EFI_FILE_PROTOCOL **file)
{
  AssertNotNullptr(s_root, "FileSystem::s_root is nullptr.");
  const auto status = s_root->Open(s_root, file, (CHAR16 *)fileName, EFI_FILE_MODE_READ, 0);
  AssertEfiStatus(status, "Failed to open file.");
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

uint64 FileSystem::GetSize(wchar_t *fileName)
{
  EFI_FILE_PROTOCOL *file;
  OpenFile(fileName, &file);

  uint8 buf[1024];
  uintn bufSize = 1024;
  
  const auto status = file->GetInfo(file, &gEfiFileInfoGuid, &bufSize, (void *)buf);
  AssertEfiStatus(status, "Failed to get file size.");

  CloseFile(file);

  return ((EFI_FILE_INFO *)buf)->FileSize;
}

void FileSystem::Read(wchar_t *fileName, uintn *bufSize, void *buf)
{
  EFI_FILE_PROTOCOL *file;
  OpenFile(fileName, &file);

  const auto status = file->Read(file, bufSize, buf);
  AssertEfiStatus(status, "Failed to read file.");

  CloseFile(file);
}
