#include "platform.h"

//----------------------------------------------------------------------------------------------------
Platform::Platform(PlatformView* platform_view)
{
    m_platform_view_ = platform_view;
    m_platform_position_ = Vector2(100, 155);
}

//----------------------------------------------------------------------------------------------------
Platform::~Platform()
{
    free(m_platform_view_);
}

//----------------------------------------------------------------------------------------------------
void Platform::Update(float delta)
{
    const auto platform_size = Vector2(m_platform_width_, m_platform_height_);
    m_platform_view_->Display(m_platform_position_, platform_size);
}

//----------------------------------------------------------------------------------------------------
void Platform::Move(Vector2 move_vector)
{
    m_platform_position_ = Vector2(m_platform_position_.X() + move_vector.X(), m_platform_position_.Y() + move_vector.Y());
}

//----------------------------------------------------------------------------------------------------
