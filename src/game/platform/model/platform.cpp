#include "platform.hpp"

arkanoid::Platform::Platform(SharedPointer<PlatformView> &platform_view) : platform_view_(platform_view)
{
    SetPosition(arkanoid::Vector2(100, 155));
}

void arkanoid::Platform::Update(float delta)
{
    platform_view_->Display(GetPosition());
}

void arkanoid::Platform::Move(arkanoid::Vector2 move_vector)
{
    Vector2 position = GetPosition();
    SetPosition(arkanoid::Vector2(position.X() + move_vector.X(), position.Y() + move_vector.Y()));
}
