#include "StageReader.hpp"

#include "System/Assert.hpp"
#include "System/Logger.hpp"
#include "System/FileSystem.hpp"
#include "Utils/BinaryArray.hpp"

Stage StageReader::read() const
{
  BinaryArray mapData = FileSystem::Read(m_fileName);

  Assert(mapData.size() >= sizeof(uint8) * 3 + sizeof(uint16) * 5, "Map data size is invalid.");

  Assert(
    mapData.read() == 'U' &&
    mapData.read() == 'M' &&
    mapData.read() == 'P',
    "Font data is invalid."
  );

  Array<uint16> realMapData((mapData.size() - 3) / 2);
  realMapData.data() = (uint16 *)&mapData[3];

  const uint16 gridSize = realMapData[0];
  const Point stageSize = { realMapData[1], realMapData[2] };
  const uint16 lineSize = realMapData[3];
  const uint16 updraftSize = realMapData[4];

  Stage stage(gridSize * Vec2(stageSize));

  for (uint16 i = 0; i < lineSize; i++)
  {
    const auto *lineData = &realMapData[5 + 4 * i];
    stage.lines().emplace(
      gridSize * lineData[0],
      gridSize * lineData[1],
      gridSize * lineData[2],
      gridSize * lineData[3]
    );
  }

  for (uint16 i = 0; i < updraftSize; i++)
  {
    const auto *updraftData = &realMapData[5 + 4 * lineSize + 4 * i];
    stage.updrafts().emplace(
      gridSize * updraftData[0],
      gridSize * updraftData[1],
      gridSize * updraftData[2],
      gridSize * updraftData[3]
    );
  }

  return stage;
}
