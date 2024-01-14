#include "level.h"

Level::Level(const std::array<std::array<char, 12>, 14> &map, const LevelView &level_view)
    : m_level_view_(level_view), m_map_(map) { }

void Level::Update(const float &delta)
{
    m_level_view_.Display(m_map_);
}
