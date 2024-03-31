#include "platform.h"

Platform::Platform(std::unique_ptr<PlatformView> &&platform_view) : m_platform_view_(std::move(platform_view))
{
    m_platform_position_ = Box2D::Vec2(100, 155);
}

void Platform::Update(float delta)
{
    m_platform_view_->Display(m_platform_position_);
}

void Platform::Move(Box2D::Vec2 move_vector)
{
    m_platform_position_ = Box2D::Vec2(m_platform_position_.x + move_vector.x, m_platform_position_.y + move_vector.y);
}
