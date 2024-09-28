#include "platform.hpp"

arkanoid::Platform::Platform(SharedPointer<PlatformView> &platform_view) : m_platform_view_(platform_view)
{
    m_platform_position_ = box2d::Vector2(100, 155);
}

void arkanoid::Platform::Update(float delta)
{
    m_platform_view_->Display(m_platform_position_);
}

void arkanoid::Platform::Move(box2d::Vector2 move_vector)
{
    m_platform_position_ = box2d::Vector2(m_platform_position_.m_x_ + move_vector.m_x_, m_platform_position_.m_y_ + move_vector.m_y_);
}
