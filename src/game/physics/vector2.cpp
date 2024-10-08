#include "vector2.hpp"

arkanoid::Vector2::Vector2()
{
    m_x = 0.0f;
    m_y = 0.0f;
}

arkanoid::Vector2::Vector2(float x, float y)
{
    m_x = x;
    m_y = y;
}

arkanoid::Vector2::Vector2(int x, int y)
{
    m_x = static_cast<float>(x);
    m_y = static_cast<float>(y);
}

float arkanoid::Vector2::X() const
{
    return m_x;
}

float arkanoid::Vector2::Y() const
{
    return m_y;
}
