#include "vector2.hpp"

namespace arkanoid
{
Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator+(Vector2 &other) const
{
    return Vector2(X() + other.X(), Y() + other.Y());
}

Vector2 Vector2::operator-(Vector2 &other) const
{
    return Vector2(X() - other.X(), Y() - other.Y());
}

Vector2 Vector2::operator*(float number) const
{
    return Vector2(X() * number, Y() * number);
}

Vector2 Vector2::operator/(float number) const
{
    return Vector2(X() / number, Y() / number);
}

Vector2 Vector2::operator=(Vector2 &vector)
{
    x = vector.X();
    y = vector.Y();
    return *this;
}
}
