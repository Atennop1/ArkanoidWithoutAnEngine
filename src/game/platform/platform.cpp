#include "game/platform/platform.hpp"
#include "game/wall/wall.hpp"

namespace arkanoid
{
Platform::Platform(genesis::PhysicalProperties properties, genesis::SharedPointer<PlatformView> &platform_view)
    : IGameObject(properties), platform_view_(platform_view) { }

void Platform::Move(genesis::Vector2 move_vector)
{
    Properties().position += move_vector;
}

void Platform::Update(float delta)
{
    platform_view_->Display(Properties().position);
}

void Platform::HandleCollisionStart(IPhysicsObject *other)
{
    if (Wall* wall = dynamic_cast<Wall*>(other); wall == nullptr)
        return;

    float overlap_left = Properties().Right() - other->Properties().Left();
    float overlap_right = other->Properties().Right() - Properties().Left();

    bool platform_from_left = abs(overlap_left) < abs(overlap_right);
    Move({ platform_from_left ? -overlap_left : overlap_right, 0 });
}
}