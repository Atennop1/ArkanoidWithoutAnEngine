#pragma once

#include "Windows.h"
#include "../../DTOs/RenderPack/RenderPack.h"
#include "../../DTOs/Vector2/Vector2.h"

class PlatformRenderer
{
private:
    const int PLATFORM_CIRCLE_SIZE = 7;
    const int PLATFORM_WIDTH = 21;

    HPEN m_whitePen;
    RenderPack m_violetRenderPack;
    RenderPack m_blueRenderPack;

public:
    PlatformRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack, HPEN whitePen);
    void Render(HDC hdc, Vector2 position) const;
};

