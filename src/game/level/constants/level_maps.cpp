#include "game/level/level_map.hpp"
#include "game/level/constants/level_maps.hpp"
#include "game/level/constants/level_layouts.hpp"

namespace arkanoid
{
LevelMap LevelMaps::kFirst = LevelMap(LevelLayouts::First());
}
