#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_VECTOR2_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_VECTOR2_HPP_

namespace arkanoid
{
    struct Vector2
    {
    private:
        float m_x;
        float m_y;

    public:
        Vector2();
        Vector2(float x, float y);
        Vector2(int x, int y);

        float X() const;
        float Y() const;
    };
}

#endif
