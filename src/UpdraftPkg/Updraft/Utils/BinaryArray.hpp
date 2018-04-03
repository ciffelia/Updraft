#pragma once

#include "Types.hpp"
#include "Array.hpp"

struct BinaryArray : Array<uint8>
{
  uintn pos = 0;

  using Array<uint8>::Array;

  void skip(const uintn offset);

  uint8 read();

  uint8 read(const uintn _pos);
};
