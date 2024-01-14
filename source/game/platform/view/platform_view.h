#pragma once
#include "../../dtos/window_references/window_references.h"

class PlatformView
{
private:
    SDL_Texture *m_platform_texture_;
    const WindowReferences &m_window_references_;

public:
    explicit PlatformView(const WindowReferences &window_references);
    ~PlatformView();
    
    void Display(Vector2 position) const;
};

