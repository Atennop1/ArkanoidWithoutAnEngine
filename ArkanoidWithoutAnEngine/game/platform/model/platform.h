#pragma once
#include "../../DTOs/Vector2/vector2.h"
#include "../View/platform_view.h"

class Platform
{
private:
    Vector2 m_platform_position_;
    PlatformView *m_platform_view_;

    int m_platform_width_ = 21;
    const int m_platform_height_ = 7;
    
public:
    Platform(PlatformView *platform_view);
    void Move(Vector2 move_vector);
};
