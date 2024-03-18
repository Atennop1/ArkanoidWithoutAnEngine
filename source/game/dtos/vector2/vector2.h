#ifndef ARKANOIDWITHOUTANENGINE_CE7F7BC940034A2092B12F6D6FAF9A58
#define ARKANOIDWITHOUTANENGINE_CE7F7BC940034A2092B12F6D6FAF9A58

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

#endif
