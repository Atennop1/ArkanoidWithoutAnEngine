#include "platform.hpp"

namespace arkanoid
{
Platform::Platform(PhysicalProperties properties, SharedPointer<PlatformView> &platform_view)
    : IGameObject(properties), platform_view_(platform_view) { }

void Platform::Update(float delta)
{
    platform_view_->Display(Properties().position);
}

void Platform::Move(Vector2 move_vector)
{
    Properties().position += move_vector;
}
}