#pragma once

#include "Windows.h"
#include "../RenderPack/RenderPack.h"

class PlatformRenderer
{
private:
    const int PLATFORM_CIRCLE_SIZE = 7;
    const int PLATFORM_WIDTH = 21;

    RenderPack m_violetRenderPack;
    RenderPack m_blueRenderPack;

public:
    PlatformRenderer(RenderPack violetRenderPack, RenderPack blueRenderPack);
    void Render(HDC hdc, int x, int y) const;
};

