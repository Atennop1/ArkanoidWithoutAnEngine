#include "level_map.hpp"
#include "../constants/level_layouts.hpp"
#include <stdexcept>

arkanoid::LevelMap::LevelMap()
    : m_map_(LevelLayouts::Empty()) { }

arkanoid::LevelMap::LevelMap(std::array<std::array<char, 12>, 14> &map)
    : m_map_(map) { }

std::array<char, 12> arkanoid::LevelMap::operator[](int index) const
{
    if (index > 13)
        throw std::out_of_range("Level cannot contain more than 14 rows of tiles");

    return (m_map_)[index];
}
