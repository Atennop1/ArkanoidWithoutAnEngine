#pragma once

#include "../../DTOs/Vector2/int_vector2.h"
#include "../../DTOs/window_handles/window_handles.h"

class PlatformView
{
private:
    WindowHandles *m_window_handles_;
    IntVector2 m_last_platform_position_;

public:
    PlatformView(WindowHandles *window_handles);
    ~PlatformView();
    
    void Display(IntVector2 position, IntVector2 size);
};

