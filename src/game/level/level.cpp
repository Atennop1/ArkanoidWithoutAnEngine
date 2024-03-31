#include "level.hpp"

Level::Level(std::unique_ptr<LevelMap> &&map, std::unique_ptr<LevelView> &&level_view)
    : m_level_view_(std::move(level_view)), m_map_(std::move(map)) { }

void Level::Update(float delta)
{
    m_level_view_->Display(*m_map_);
}
