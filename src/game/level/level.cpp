#include "level.hpp"

arkanoid::Level::Level(const LevelMap &map, const SharedPointer<LevelView> &level_view)
    : level_view_(level_view), map_(map) { }

void arkanoid::Level::Update(float delta)
{
    level_view_->Display(map_);
}
