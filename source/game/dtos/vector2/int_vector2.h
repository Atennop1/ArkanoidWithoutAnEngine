#ifndef ARKANOIDWITHOUTANENGINE_7EAA7E8723DB4A57B28F0AD5B213ADA8
#define ARKANOIDWITHOUTANENGINE_7EAA7E8723DB4A57B28F0AD5B213ADA8

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

#endif
