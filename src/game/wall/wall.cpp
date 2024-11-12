#include "game/wall/wall.hpp"

namespace arkanoid
{
Wall::Wall(genesis::PhysicalProperties physical_properties, const genesis::SharedPointer<WallView> &wall_view)
    : IGameObject(physical_properties), wall_view_(wall_view) { }

void Wall::Update(float delta)
{
    wall_view_->Display(Properties().position);
}
}