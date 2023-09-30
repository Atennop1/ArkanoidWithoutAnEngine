#include "platform_view.h"
#include "../../view/visualization_consts.h"
#include "../../Shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
PlatformView::PlatformView(WindowHandles *window_handles, RenderPack *violet_render_pack, RenderPack *blue_render_pack, HPEN white_pen)
{
    m_violet_render_pack_ = violet_render_pack;
    m_blue_render_pack_ = blue_render_pack;
    m_white_pen_ = white_pen;
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void PlatformView::Display(Vector2 position) const
{
    const HDC hdc = *m_window_handles_->HDC();
    const int x = position.X();
    const int y = position.Y();
    
    Shortcuts::SelectRenderPack(hdc, *m_violet_render_pack_);
    Ellipse(hdc, x * kScaleMultiplier, y * kScaleMultiplier, (x + kPlatformCircleSize) * kScaleMultiplier, (y + kPlatformCircleSize) * kScaleMultiplier);
    Ellipse(hdc, (x + kPlatformWidth) * kScaleMultiplier, y * kScaleMultiplier, (x + kPlatformCircleSize + kPlatformWidth) * kScaleMultiplier, (y + kPlatformCircleSize) * kScaleMultiplier);

    Shortcuts::SelectRenderPack(hdc, *m_blue_render_pack_);
    RoundRect(hdc, (x + 3) * kScaleMultiplier, (y + 1) * kScaleMultiplier, (x + 5 + kPlatformWidth - 1) * kScaleMultiplier, (y + 1 + 5) * kScaleMultiplier, 3 * kScaleMultiplier, 3 * kScaleMultiplier);

    SelectObject(hdc, m_white_pen_);
    Arc(hdc, (x + 1) * kScaleMultiplier, (y + 1) * kScaleMultiplier, (x + kPlatformCircleSize - 1) * kScaleMultiplier, (y + kPlatformCircleSize - 1) * kScaleMultiplier,
        (x + 1 + 1) * kScaleMultiplier, (y + 1) * kScaleMultiplier, (x + 1) * kScaleMultiplier, (y + 1 + 2) * kScaleMultiplier);
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
    free(m_blue_render_pack_);
    free(m_violet_render_pack_);
}

//----------------------------------------------------------------------------------------------------
