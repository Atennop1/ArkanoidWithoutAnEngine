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
void PlatformView::Display(IntVector2 position, IntVector2 size)
{
    const HDC hdc = *m_window_handles_->HDC();

    Shortcuts::SelectRenderPack(hdc, *m_background_render_pack_);
    Rectangle(hdc, m_last_platform_position_.X() * kScaleMultiplier, m_last_platform_position_.Y() * kScaleMultiplier, (m_last_platform_position_.X() + size.X() + size.Y()) * kScaleMultiplier, (m_last_platform_position_.Y() + size.X() + size.Y()) * kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, *m_violet_render_pack_);
    Ellipse(hdc, position.X() * kScaleMultiplier, position.Y() * kScaleMultiplier, (position.X() + size.Y()) * kScaleMultiplier, (position.Y() + size.Y()) * kScaleMultiplier);
    Ellipse(hdc, (position.X() + size.X()) * kScaleMultiplier, position.Y() * kScaleMultiplier, (position.X() + size.Y() + size.X()) * kScaleMultiplier, (position.Y() + size.Y()) * kScaleMultiplier);

    Shortcuts::SelectRenderPack(hdc, *m_blue_render_pack_);
    RoundRect(hdc, (position.X() + 4) * kScaleMultiplier, (position.Y() + 1) * kScaleMultiplier, (position.X() + 4 + size.X() - 1) * kScaleMultiplier, (position.Y() + 1 + 5) * kScaleMultiplier, 3 * kScaleMultiplier, 3 * kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, *m_white_render_pack_);
    Arc(hdc, (position.X() + 1) * kScaleMultiplier, (position.Y() + 1) * kScaleMultiplier, (position.X() + size.Y() - 1) * kScaleMultiplier, (position.Y() + size.Y() - 1) * kScaleMultiplier,
        (position.X() + 1 + 1) * kScaleMultiplier, (position.Y() + 1) * kScaleMultiplier, (position.X() + 1) * kScaleMultiplier, (position.Y() + 1 + 2) * kScaleMultiplier);

    m_last_platform_position_ = position;
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
    free(m_blue_render_pack_);
    free(m_violet_render_pack_);
}

//----------------------------------------------------------------------------------------------------
