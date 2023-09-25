﻿#include "RenderPack.h"

RenderPack::RenderPack()
{
    m_pen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
    m_brush = CreateSolidBrush(RGB(255, 255, 255));
}

RenderPack::RenderPack(COLORREF color)
{
    m_pen = CreatePen(PS_SOLID, 0, color);
    m_brush = CreateSolidBrush(color);
}

RenderPack::RenderPack(HPEN pen, HBRUSH brush)
{
    m_pen = pen;
    m_brush = brush;
}

HPEN RenderPack::Pen() const
{
    return m_pen;
}

HBRUSH RenderPack::Brush() const
{
    return m_brush;
}


