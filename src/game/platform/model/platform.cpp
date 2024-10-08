#include "platform.hpp"

arkanoid::Platform::Platform(SharedPointer<PlatformView> &platform_view) : platform_view_(platform_view)
{
    platform_position_ = arkanoid::Vector2(100, 155);
}

void arkanoid::Platform::Update(float delta)
{
    platform_view_->Display(platform_position_);
}

void arkanoid::Platform::Move(arkanoid::Vector2 move_vector)
{
  platform_position_ = arkanoid::Vector2(platform_position_.X() + move_vector.X(), platform_position_.Y() + move_vector.Y());
}
