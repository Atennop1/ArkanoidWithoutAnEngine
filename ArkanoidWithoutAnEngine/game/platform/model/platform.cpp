#include "platform.h"

//----------------------------------------------------------------------------------------------------
Platform::Platform(PlatformView* platform_view)
{
    m_platform_view_ = platform_view;
    m_platform_position_ = Vector2(100, 155);
}

//----------------------------------------------------------------------------------------------------
void Platform::Move(Vector2 move_vector)
{
    m_platform_position_ = Vector2(m_platform_position_.X() + move_vector.X(), m_platform_position_.Y() + move_vector.Y());
    m_platform_view_->Display(m_platform_position_);
}

//----------------------------------------------------------------------------------------------------
