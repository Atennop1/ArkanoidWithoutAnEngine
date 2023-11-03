#pragma once
#include "../../dtos/window_references/window_references.h"

class PlatformView
{
private:
    SDL_Texture *m_platform_texture_;
    SDL_Rect m_displaying_rect_;

    WindowReferences *m_window_handles_;

public:
    PlatformView(WindowReferences *window_handles);
    ~PlatformView();
    
    void Display(Vector2 position);
};

