#pragma once

#include "Windows.h"
#include "../../DTOs/render_pack/render_pack.h"
#include "../../DTOs/Vector2/vector2.h"
#include "../../DTOs/window_handles/window_handles.h"

class PlatformView
{
private:
    const int kPlatformCircleSize = 7;
    const int kPlatformWidth = 21;

    HPEN m_white_pen_;
    RenderPack *m_violet_render_pack_;
    RenderPack *m_blue_render_pack_;

    WindowHandles *m_window_handles_;

public:
    PlatformView(WindowHandles *window_handles, RenderPack *violet_render_pack, RenderPack *blue_render_pack, HPEN white_pen);
    ~PlatformView();
    
    void Display(Vector2 position) const;
};

