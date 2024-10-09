#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_MATH_VECTOR2_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_MATH_VECTOR2_HPP_

#include <cmath>

namespace arkanoid
{
struct Vector2
{
private:
    float m_x;
    float m_y;

public:
    Vector2(float x = 0, float y = 0);

    float X() const { return m_x; }
    float Y() const { return m_y; }

    float Magnitude() const { return std::sqrt(std::pow(X(), 2) + std::pow(Y(), 2)); }
    float SquaredMagnitude() const { return std::pow(Magnitude(), 2); }
    Vector2 Normalized() const { return *this / Magnitude(); }

    Vector2 operator+(Vector2 &other) const;
    Vector2 operator+(Vector2 &&other) const { return operator+(other); }

    Vector2 operator-(Vector2 &other) const;
    Vector2 operator-(Vector2 &&other) const { return operator-(other); }

    Vector2 operator*(float number) const;
    Vector2 operator/(float number) const;
};
}

#endif
