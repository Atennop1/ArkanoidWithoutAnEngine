#include "game/level/level.hpp"

namespace arkanoid
{
Level::Level(const std::vector<std::vector<SharedPointer<Brick>>> &map, const SharedPointer<LevelView> &level_view)
    : map_(map), level_view_(level_view) { }

void Level::Update(float delta)
{
    level_view_->Display(map_);
}
}
