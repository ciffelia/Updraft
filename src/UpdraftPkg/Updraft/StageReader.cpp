#include "StageReader.hpp"

#include "System/Assert.hpp"
#include "System/Logger.hpp"
#include "System/FileSystem.hpp"

void StageReader::readMapData(uint16 **mapData) const
{
  uint8 *mapFileData;

  uintn bufSize = FileSystem::GetSize(m_fileName);
  mapFileData = new uint8[bufSize];

  FileSystem::Read(m_fileName, &bufSize, mapFileData);

  Assert(mapFileData[0] == 'U' && mapFileData[1] == 'M' && mapFileData[2] == 'P', "Map magic number is invalid.");
  Assert(bufSize >= sizeof(uint8) * 3 + sizeof(uint16) * 5, "Map data size is invalid.");

  (*mapData) = (uint16 *)(&mapFileData[3]);
}

Stage StageReader::read() const
{
  uint16 *mapData;

  readMapData(&mapData);

  const uint16 gridSize = mapData[0];
  const Point m_stageSize = {mapData[1], mapData[2]};
  const uint16 lineSize = mapData[3];
  const uint16 updraftSize = mapData[4];

  Stage stage(gridSize, m_stageSize, lineSize, updraftSize);

  delete[] mapData;

  return stage;
}
