#include "game/level/level.hpp"

namespace arkanoid
{
Level::Level(const LevelMap &map, const SharedPointer<LevelView> &level_view)
    : level_view_(level_view), map_(map) {}

void Level::Update(float delta)
{
    level_view_->Display(map_);
}
}
