#pragma once

struct IntVector2
{
private:
    int m_x_;
    int m_y_;
    
public:
    IntVector2();
    IntVector2(int x, int y);
    IntVector2(float x, float y);

    int X() const;
    int Y() const;
};
