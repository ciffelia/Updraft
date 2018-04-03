#include "BinaryArray.hpp"

void BinaryArray::skip(const uintn offset)
{
  pos += offset;
}

uint8 BinaryArray::read()
{
  return this->at(pos++);
}

uint8 BinaryArray::read(const uintn _pos)
{
  pos = _pos;

  return this->at(pos++);
}
