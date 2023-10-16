#include "platform_view.h"
#include "../../view/visualization_consts.h"
#include "../../Shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
PlatformView::PlatformView(WindowHandles *window_handles, RenderPack *white_render_pack, RenderPack *black_render_pack, RenderPack *violet_render_pack, RenderPack *blue_render_pack)
{
    m_window_handles_ = window_handles;

    m_white_render_pack_ = white_render_pack;
    m_background_render_pack_ = black_render_pack;
    m_violet_render_pack_ = violet_render_pack;
    m_blue_render_pack_ = blue_render_pack;
}

//----------------------------------------------------------------------------------------------------
void PlatformView::Display(Vector2 position, Vector2 size)
{
    const HDC hdc = *m_window_handles_->HDC();
    const int position_x = static_cast<int>(position.X());
    const int position_y = static_cast<int>(position.Y());
    
    const int size_x = static_cast<int>(size.X());
    const int size_y = static_cast<int>(size.Y());

    Shortcuts::SelectRenderPack(hdc, *m_background_render_pack_);
    Rectangle(hdc, static_cast<int>(last_platform_position.X()) * kScaleMultiplier, static_cast<int>(last_platform_position.Y()) * kScaleMultiplier, (static_cast<int>(last_platform_position.X()) + size_x + size_y) * kScaleMultiplier, (static_cast<int>(last_platform_position.Y()) + size_x + size_y) * kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, *m_violet_render_pack_);
    Ellipse(hdc, position_x * kScaleMultiplier, position_y * kScaleMultiplier, (position_x + size_y) * kScaleMultiplier, (position_y + size_y) * kScaleMultiplier);
    Ellipse(hdc, (position_x + size_x) * kScaleMultiplier, position_y * kScaleMultiplier, (position_x + size_y + size_x) * kScaleMultiplier, (position_y + size_y) * kScaleMultiplier);

    Shortcuts::SelectRenderPack(hdc, *m_blue_render_pack_);
    RoundRect(hdc, (position_x + 4) * kScaleMultiplier, (position_y + 1) * kScaleMultiplier, (position_x + 4 + size_x - 1) * kScaleMultiplier, (position_y + 1 + 5) * kScaleMultiplier, 3 * kScaleMultiplier, 3 * kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, *m_white_render_pack_);
    Arc(hdc, (position_x + 1) * kScaleMultiplier, (position_y + 1) * kScaleMultiplier, (position_x + size_y - 1) * kScaleMultiplier, (position_y + size_y - 1) * kScaleMultiplier,
        (position_x + 1 + 1) * kScaleMultiplier, (position_y + 1) * kScaleMultiplier, (position_x + 1) * kScaleMultiplier, (position_y + 1 + 2) * kScaleMultiplier);

    last_platform_position = position;
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
    free(m_blue_render_pack_);
    free(m_violet_render_pack_);
}

//----------------------------------------------------------------------------------------------------
