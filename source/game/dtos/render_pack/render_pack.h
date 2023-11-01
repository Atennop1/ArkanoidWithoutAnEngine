#pragma once
#include "windows.h"

struct RenderPack
{
private:
    HPEN m_pen_;
    HBRUSH m_brush_;
    
public:
    RenderPack();
    RenderPack(COLORREF color);
    RenderPack(HPEN pen, HBRUSH brush);
    
    HPEN Pen() const;
    HBRUSH Brush() const;
};