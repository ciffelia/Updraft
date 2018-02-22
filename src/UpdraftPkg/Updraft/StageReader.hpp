#pragma once

#include "Stage.hpp"

class StageReader
{
  const wchar_t *m_fileName;

  void readMapData(uint16 **mapData) const;

public:
  explicit StageReader(const wchar_t *_fileName)
    : m_fileName(_fileName)
  { }

  Stage read() const;
};
