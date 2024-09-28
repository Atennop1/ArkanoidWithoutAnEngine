#include "level.hpp"

arkanoid::Level::Level(const LevelMap &map, const SharedPointer<LevelView> &level_view)
    : m_level_view_(level_view), m_map_(map) { }

void arkanoid::Level::Update(float delta)
{
    m_level_view_->Display(m_map_);
}
