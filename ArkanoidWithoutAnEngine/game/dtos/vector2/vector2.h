#pragma once

struct Vector2
{
private:
    int m_x;
    int m_y;
    
public:
    Vector2();
    Vector2(int x, int y);

    int X() const;
    int Y() const;
};
