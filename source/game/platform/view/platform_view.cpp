#include "platform_view.h"
#include "../../rendering/rendering_constants.h"
#include "../../shortcuts/render_colors.h"
#include "../../Shortcuts/shortcuts.h"

//----------------------------------------------------------------------------------------------------
PlatformView::PlatformView(WindowReferences *window_handles)
{
    m_window_handles_ = window_handles;
}

//----------------------------------------------------------------------------------------------------
void PlatformView::Display(Vector2 position, Vector2 size) const
{
    const HDC hdc = *m_window_handles_->HDC();
    
    Shortcuts::SelectRenderPack(hdc, RenderColors::kVioletColor);
    Ellipse(hdc, static_cast<int>(position.X() * RenderingConstants::kScaleMultiplier), static_cast<int>(position.Y() * RenderingConstants::kScaleMultiplier), static_cast<int>((position.X() + size.Y()) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + size.Y()) * RenderingConstants::kScaleMultiplier));
    Ellipse(hdc, static_cast<int>((position.X() + size.X()) * RenderingConstants::kScaleMultiplier), static_cast<int>(position.Y() * RenderingConstants::kScaleMultiplier), static_cast<int>((position.X() + size.Y() + size.X()) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + size.Y()) * RenderingConstants::kScaleMultiplier));

    Shortcuts::SelectRenderPack(hdc, RenderColors::kBlueColor);
    RoundRect(hdc, static_cast<int>((position.X() + 4) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + 1) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.X() + 4 + size.X() - 1) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + 1 + 5) * RenderingConstants::kScaleMultiplier), 3 * RenderingConstants::kScaleMultiplier, 3 * RenderingConstants::kScaleMultiplier);
    
    Shortcuts::SelectRenderPack(hdc, RenderColors::kWhiteColor);
    Arc(hdc, static_cast<int>((position.X() + 1) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + 1) * RenderingConstants::kScaleMultiplier), static_cast<int>(RenderingConstants::kScaleMultiplier * (size.Y() + position.X() - 1)), static_cast<int>((position.Y() + size.Y() - 1) * RenderingConstants::kScaleMultiplier),
        static_cast<int>((position.X() + 1 + 2) * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + 1) * RenderingConstants::kScaleMultiplier), static_cast<int>(position.X() * RenderingConstants::kScaleMultiplier), static_cast<int>((position.Y() + 1 + 2) * RenderingConstants::kScaleMultiplier));
}

//----------------------------------------------------------------------------------------------------
PlatformView::~PlatformView()
{
    free(m_window_handles_);
}

//----------------------------------------------------------------------------------------------------
