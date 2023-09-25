#pragma once
#include "Windows.h"

class RenderPack
{
private:
    HPEN m_pen;
    HBRUSH m_brush;
    
public:
    RenderPack();
    RenderPack(COLORREF color);
    RenderPack(HPEN pen, HBRUSH brush);
    
    HPEN Pen() const;
    HBRUSH Brush() const;
};