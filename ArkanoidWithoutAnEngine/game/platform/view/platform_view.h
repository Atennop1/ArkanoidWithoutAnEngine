#pragma once
#include "../../DTOs/window_handles/window_handles.h"

class PlatformView
{
private:
    WindowHandles *m_window_handles_;

public:
    PlatformView(WindowHandles *window_handles);
    ~PlatformView();
    
    void Display(Vector2 position, Vector2 size) const;
};

