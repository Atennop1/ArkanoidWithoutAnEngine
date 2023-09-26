#pragma once

#include "Windows.h"
#include "../../DTOs/RenderPack/RenderPack.h"
#include "../../DTOs/Vector2/Vector2.h"
#include "../../DTOs/WindowHandles/WindowHandles.h"

class PlatformView
{
private:
    const int PLATFORM_CIRCLE_SIZE = 7;
    const int PLATFORM_WIDTH = 21;
    
    RenderPack *m_violetRenderPack;
    RenderPack *m_blueRenderPack;
    HPEN m_whitePen;

    WindowHandles *m_windowHandles;

public:
    PlatformView(WindowHandles *windowHandles, RenderPack *violetRenderPack, RenderPack *blueRenderPack, HPEN whitePen);
    ~PlatformView();
    
    void Display(Vector2 position) const;
};

