#include <memory>
#include <stdexcept>
#include "level_map.hpp"

LevelMap::LevelMap() : m_map_(std::make_unique<std::array<std::array<char, 12>, 14>>(
std::array<std::array<char, 12>, 14>
{{
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }}
}})) { }

LevelMap::LevelMap(std::unique_ptr<std::array<std::array<char, 12>, 14>> &&map)
    : m_map_(std::move(map)) { }

std::array<char, 12> LevelMap::operator[](int index) const
{
    if (index > 13)
        throw std::out_of_range("Level cannot contain more than 14 rows of tiles");

    return (*m_map_)[index];
}
