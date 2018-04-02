#include "Array.hpp"

struct BinaryArray : Array<uint8>
{
  uintn pos;

  using Array<uint8>::Array;

  void skip(const uintn offset);

  uint8 read();

  uint8 read(const uintn _pos);
};
