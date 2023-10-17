#pragma once

#include "../../DTOs/render_pack/render_pack.h"
#include "../../DTOs/Vector2/int_vector2.h"
#include "../../DTOs/window_handles/window_handles.h"

class PlatformView
{
private:
    RenderPack *m_white_render_pack_;
    RenderPack *m_background_render_pack_;
    RenderPack *m_violet_render_pack_;
    RenderPack *m_blue_render_pack_;

    WindowHandles *m_window_handles_;
    IntVector2 m_last_platform_position_;

public:
    PlatformView(WindowHandles *window_handles, RenderPack *white_render_pack, RenderPack *black_render_pack, RenderPack *violet_render_pack, RenderPack *blue_render_pack);
    ~PlatformView();
    
    void Display(IntVector2 position, IntVector2 size);
};

