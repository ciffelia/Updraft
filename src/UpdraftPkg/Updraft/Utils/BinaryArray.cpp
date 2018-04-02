#include "BinaryArray.hpp"

void BinaryArray::skip(const uintn offset)
{
  pos += offset;
}

uint8 BinaryArray::read()
{
  return read(pos);
}

uint8 BinaryArray::read(const uintn _pos)
{
  pos = _pos + 1;

  return this->at(pos);
}
