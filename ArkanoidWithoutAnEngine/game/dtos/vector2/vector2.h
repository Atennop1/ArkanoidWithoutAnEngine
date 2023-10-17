#pragma once

struct Vector2
{
private:
    float m_x_;
    float m_y_;
    
public:
    Vector2();
    Vector2(float x, float y);
    Vector2(int x, int y);

    float X() const;
    float Y() const;
};
