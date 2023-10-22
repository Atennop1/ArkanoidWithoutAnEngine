#include "platform_view.h"
#include "../../rendering/rendering_consts.h"
#include "../../shortcuts/render_packs.h"
#include "../../Shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
PlatformView::PlatformView(WindowHandles *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void PlatformView::Display(Vector2 position, Vector2 size) const
{
    const HDC hdc = *m_window_handles_->HDC();
    
    Shortcuts::SelectRenderPack(hdc, RenderPacks::kVioletRenderPack);
    Ellipse(hdc, static_cast<int>(position.X() * kScaleMultiplier), static_cast<int>(position.Y() * kScaleMultiplier), static_cast<int>((position.X() + size.Y()) * kScaleMultiplier), static_cast<int>((position.Y() + size.Y()) * kScaleMultiplier));
    Ellipse(hdc, static_cast<int>((position.X() + size.X()) * kScaleMultiplier), static_cast<int>(position.Y() * kScaleMultiplier), static_cast<int>((position.X() + size.Y() + size.X()) * kScaleMultiplier), static_cast<int>((position.Y() + size.Y()) * kScaleMultiplier));

    Shortcuts::SelectRenderPack(hdc, RenderPacks::kBlueRenderPack);
    RoundRect(hdc, static_cast<int>((position.X() + 4) * kScaleMultiplier), static_cast<int>((position.Y() + 1) * kScaleMultiplier), static_cast<int>((position.X() + 4 + size.X() - 1) * kScaleMultiplier), static_cast<int>((position.Y() + 1 + 5) * kScaleMultiplier), 3 * kScaleMultiplier, 3 * kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, RenderPacks::kWhiteRenderPack);
    Arc(hdc, static_cast<int>((position.X() + 1) * kScaleMultiplier), static_cast<int>((position.Y() + 1) * kScaleMultiplier), static_cast<int>((position.X() + size.Y() - 1) * kScaleMultiplier), static_cast<int>((position.Y() + size.Y() - 1) * kScaleMultiplier),
        static_cast<int>((position.X() + 1 + 1) * kScaleMultiplier), static_cast<int>((position.Y() + 1) * kScaleMultiplier), static_cast<int>((position.X() + 1) * kScaleMultiplier), static_cast<int>((position.Y() + 1 + 2) * kScaleMultiplier));
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------
