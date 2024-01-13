#include "vector2.h"

Vector2::Vector2()
{
    m_x_ = 0.0f;
    m_y_ = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    m_x_ = x;
    m_y_ = y;
}

Vector2::Vector2(int x, int y)
{
    m_x_ = static_cast<float>(x);
    m_y_ = static_cast<float>(y);
}

float Vector2::X() const
{
    return m_x_;
}

float Vector2::Y() const
{
    return m_y_;
}
