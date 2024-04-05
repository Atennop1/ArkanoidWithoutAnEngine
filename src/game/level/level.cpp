#include "level.hpp"

Level::Level(const LevelMap &map, const LevelView &level_view)
    : m_level_view_(level_view), m_map_(map) { }

void Level::Update(float delta)
{
    m_level_view_.Display(m_map_);
}
