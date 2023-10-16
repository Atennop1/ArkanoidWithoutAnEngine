#pragma once

struct Vector2
{
private:
    float m_x;
    float m_y;
    
public:
    Vector2();
    Vector2(float x, float y);

    float X() const;
    float Y() const;
};
