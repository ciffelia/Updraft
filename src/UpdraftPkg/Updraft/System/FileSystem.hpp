#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/SimpleFileSystem.h>
}

#include "../Utils/Array.hpp"
#include "../Utils/Types.hpp"

struct FileSystem
{
  static EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *s_SimpleFileSystemProtocol;

  static EFI_FILE_PROTOCOL *s_root;

  static void LocateSimpleFileSystemProtocol();

  static void OpenVolume();

  static void OpenFile(const wchar_t *fileName, EFI_FILE_PROTOCOL **file);

  static void CloseFile(EFI_FILE_PROTOCOL *file);

public:
  static void Initialize();

  static uint64 GetSize(const wchar_t *fileName);

  static void Read(const wchar_t *fileName, uintn *bufSize, void *buf);

  static Array<uint8> Read(const wchar_t *fileName);
};
