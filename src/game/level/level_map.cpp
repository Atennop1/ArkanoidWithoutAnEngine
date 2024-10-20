#include <stdexcept>
#include "game/level/level_map.hpp"
#include "game/level/constants/level_layouts.hpp"

namespace arkanoid
{
LevelMap::LevelMap()
    : map_(LevelLayouts::Empty()) { }

LevelMap::LevelMap(std::array<std::array<char, 12>, 14> &map)
    : map_(map) { }

std::array<char, 12> LevelMap::operator[](int index) const
{
    if (index > 13)
        throw std::out_of_range("Level cannot contain more than 14 rows of tiles");

    return map_[index];
}
}
