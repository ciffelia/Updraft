#include "Utility.hpp"

extern "C" {
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
}

void _Swap(void *a, void *b, const size_t size)
{
  void *t = AllocatePool(size);
  CopyMem(t, a, size);

  CopyMem(a, b, size);
  CopyMem(b, t, size);

  FreePool(t);
}
