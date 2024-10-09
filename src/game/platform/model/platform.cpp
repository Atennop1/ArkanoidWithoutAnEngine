#include "platform.hpp"

namespace arkanoid
{
Platform::Platform(SharedPointer<PlatformView> &platform_view) : platform_view_(platform_view)
{
    SetPosition(Vector2(100, 155));
}

void Platform::Update(float delta)
{
    platform_view_->Display(GetPosition());
}

void Platform::Move(Vector2 move_vector)
{
    Vector2 position = GetPosition();
    SetPosition(Vector2(position.X() + move_vector.X(), position.Y() + move_vector.Y()));
}
}