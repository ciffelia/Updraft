#include "StageReader.hpp"

#include "System/Assert.hpp"
#include "System/Logger.hpp"
#include "System/FileSystem.hpp"
#include "Utils/Array.hpp"

Stage StageReader::read() const
{
  Array<uint8> mapData = FileSystem::Read(m_fileName);

  Assert(mapData.size() >= sizeof(uint8) * 3 + sizeof(uint16) * 5, "Map data size is invalid.");

  Assert(
    mapData.at(0) == 'U' &&
    mapData.at(1) == 'M' &&
    mapData.at(2) == 'P',
    "Font data is invalid."
  );

  Array<uint16> realMapData((mapData.size() - 3) / 2);
  realMapData.data() = (uint16 *)&mapData[3];

  const uint16 gridSize = realMapData[0];
  const Point stageSize = { realMapData[1], realMapData[2] };
  const uint16 lineSize = realMapData[3];
  const uint16 updraftSize = realMapData[4];

  Stage stage(gridSize, stageSize, lineSize, updraftSize);

  return stage;
}
