#include <stdexcept>
#include "level_map.hpp"
#include "../constants/level_layouts.hpp"

LevelMap::LevelMap()
    : m_map_(LevelLayouts::Empty()) { }

LevelMap::LevelMap(std::array<std::array<char, 12>, 14> &map)
    : m_map_(map) { }

std::array<char, 12> LevelMap::operator[](int index) const
{
    if (index > 13)
        throw std::out_of_range("Level cannot contain more than 14 rows of tiles");

    return (m_map_)[index];
}
