#include "PlatformRenderer.h"
#include "../RenderingConsts.h"

//----------------------------------------------------------------------------------------------------
PlatformRenderer::PlatformRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack)
{
    m_violetRenderPack = violetRenderPack;
    m_blueRenderPack = blueRenderPack;
}

//----------------------------------------------------------------------------------------------------
void PlatformRenderer::Render(HDC hdc, int x, int y) const
{
    SelectObject(hdc, m_violetRenderPack.Pen());
    SelectObject(hdc, m_violetRenderPack.Brush());
    
    Ellipse(hdc, x * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);
    Ellipse(hdc, (x + PLATFORM_WIDTH) * SCALE_MULTIPLIER, y * SCALE_MULTIPLIER, (x + PLATFORM_CIRCLE_SIZE + PLATFORM_WIDTH) * SCALE_MULTIPLIER, (y + PLATFORM_CIRCLE_SIZE) * SCALE_MULTIPLIER);

    SelectObject(hdc, m_blueRenderPack.Pen());  
    SelectObject(hdc, m_blueRenderPack.Brush());
    RoundRect(hdc, (x + 3) * SCALE_MULTIPLIER, (y + 1) * SCALE_MULTIPLIER, (x + 5 + PLATFORM_WIDTH - 1) * SCALE_MULTIPLIER, (y + 1 + 5) * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER, 3 * SCALE_MULTIPLIER);
}

//----------------------------------------------------------------------------------------------------