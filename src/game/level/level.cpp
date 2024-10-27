#include "game/level/level.hpp"

namespace arkanoid
{
Level::Level(const std::vector<std::vector<SharedPointer<Brick>>> &map, const SharedPointer<LevelView> &level_view)
    : map_(map), level_view_(level_view) { }

void Level::Update(float delta)
{
    for (auto &line : map_)
        line.erase(std::remove_if(line.begin(), line.end(), [](auto brick) { return brick->IsDestroyed(); }), line.end());

    level_view_->Display(map_);
}
}
