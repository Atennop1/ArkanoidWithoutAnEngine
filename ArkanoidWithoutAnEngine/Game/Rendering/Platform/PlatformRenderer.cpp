#include "PlatformRenderer.h"
#include "../RenderingConsts.h"
#include "../../Shortcuts/Shortcuts.h"

//----------------------------------------------------------------------------------------------------
PlatformRenderer::PlatformRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack, HPEN whitePen)
{
    m_violetRenderPack = violetRenderPack;
    m_blueRenderPack = blueRenderPack;
    m_whitePen = whitePen;
}

//----------------------------------------------------------------------------------------------------
void PlatformRenderer::Render(HDC hdc, Vector2 position) const
{
    const int x = position.X;
    const int y = position.Y;
    
    Shortcuts::SelectRenderPack(hdc, m_violetRenderPack);
    Ellipse(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);
    Ellipse(hdc, (x + PLATFORM_WIDTH) * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE + PLATFORM_WIDTH) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);

    Shortcuts::SelectRenderPack(hdc, m_blueRenderPack);
    RoundRect(hdc, (x + 3) * SCALE_MULTIPLIER, (y + 1) * SCALE_MULTIPLIER, (x + 5 + PLATFORM_WIDTH - 1) * SCALE_MULTIPLIER, (y + 1 + 5) * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER);

    SelectObject(hdc, m_whitePen);
    Arc(hdc, (x + 1) * SCALE_MULTIPLIER, (y + 1) * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE - 1) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE - 1) * SCALE_MULTIPLIER,
        (x + 1 + 1) * SCALE_MULTIPLIER, (y + 1) * SCALE_MULTIPLIER, (x + 1) * SCALE_MULTIPLIER, (y + 1 + 2) * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------