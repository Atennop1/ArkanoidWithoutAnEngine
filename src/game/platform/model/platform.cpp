﻿#include "platform.hpp"

Platform::Platform(std::unique_ptr<PlatformView> &platform_view) : m_platform_view_(std::move(platform_view))
{
    m_platform_position_ = Box2D::Vector2(100, 155);
}

void Platform::Update(float delta)
{
    m_platform_view_->Display(m_platform_position_);
}

void Platform::Move(Box2D::Vector2 move_vector)
{
    m_platform_position_ = Box2D::Vector2(m_platform_position_.m_x_ + move_vector.m_x_, m_platform_position_.m_y_ + move_vector.m_y_);
}
