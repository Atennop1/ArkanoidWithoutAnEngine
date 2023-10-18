#include "platform_view.h"
#include "../../view/visualization_consts.h"
#include "../../Shortcuts/shortcuts.h"
#include "../../view/render_packs.h"

//----------------------------------------------------------------------------------------------------
PlatformView::PlatformView(WindowHandles *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void PlatformView::Display(IntVector2 position, IntVector2 size)
{
    const HDC hdc = *m_window_handles_->HDC();
    
    Shortcuts::SelectRenderPack(hdc, RenderPacks::kVioletRenderPack);
    Ellipse(hdc, position.X() * kScaleMultiplier, position.Y() * kScaleMultiplier, (position.X() + size.Y()) * kScaleMultiplier, (position.Y() + size.Y()) * kScaleMultiplier);
    Ellipse(hdc, (position.X() + size.X()) * kScaleMultiplier, position.Y() * kScaleMultiplier, (position.X() + size.Y() + size.X()) * kScaleMultiplier, (position.Y() + size.Y()) * kScaleMultiplier);

    Shortcuts::SelectRenderPack(hdc, RenderPacks::kBlueRenderPack);
    RoundRect(hdc, (position.X() + 4) * kScaleMultiplier, (position.Y() + 1) * kScaleMultiplier, (position.X() + 4 + size.X() - 1) * kScaleMultiplier, (position.Y() + 1 + 5) * kScaleMultiplier, 3 * kScaleMultiplier, 3 * kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, RenderPacks::kWhiteRenderPack);
    Arc(hdc, (position.X() + 1) * kScaleMultiplier, (position.Y() + 1) * kScaleMultiplier, (position.X() + size.Y() - 1) * kScaleMultiplier, (position.Y() + size.Y() - 1) * kScaleMultiplier,
        (position.X() + 1 + 1) * kScaleMultiplier, (position.Y() + 1) * kScaleMultiplier, (position.X() + 1) * kScaleMultiplier, (position.Y() + 1 + 2) * kScaleMultiplier);

    m_last_platform_position_ = position;
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------
