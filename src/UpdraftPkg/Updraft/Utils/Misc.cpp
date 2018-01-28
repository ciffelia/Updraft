extern "C" {
#include <Uefi.h>
#include <Library/MemoryAllocationLib.h>
}

#include <stddef.h>

void *operator new(const size_t size)
{
  return AllocateZeroPool(size);
}

void *operator new[](const size_t size)
{
  return AllocateZeroPool(size);
}

void operator delete(void *buf)
{
  FreePool(buf);
}

void operator delete[](void *buf)
{
  FreePool(buf);
}

void operator delete(void *buf, const size_t size)
{
  FreePool(buf);
}

void operator delete[](void *buf, const size_t size)
{
  FreePool(buf);
}

// Required to use LibC
int main() {}
