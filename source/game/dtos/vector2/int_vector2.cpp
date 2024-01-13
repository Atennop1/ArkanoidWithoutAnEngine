﻿#include "int_vector2.h"

IntVector2::IntVector2()
{
    m_x_ = 0;
    m_y_ = 0;
}

IntVector2::IntVector2(int x, int y)
{
    m_x_ = x;
    m_y_ = y;
}

IntVector2::IntVector2(float x, float y)
{
    m_x_ = static_cast<int>(x);
    m_y_ = static_cast<int>(y);
}

int IntVector2::X() const
{
    return m_x_;
}

int IntVector2::Y() const
{
    return m_y_;
}
