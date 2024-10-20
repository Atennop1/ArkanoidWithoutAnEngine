#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_PHYSICAL_PROPERTIES_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_PHYSICAL_PROPERTIES_HPP_

#include "game/math/vector2.hpp"

namespace arkanoid
{
struct PhysicalProperties
{
public:
    explicit PhysicalProperties(Vector2 new_position = { }, Vector2 new_size = { }, Vector2 new_velocity = { }, Vector2 new_acceleration = { })
        : position(new_position), size(new_size), velocity(new_velocity), acceleration(new_acceleration) { }

    float Left() { return position.x - size.x / 2.f; }
    float Right() { return position.x + size.x / 2.f; }
    float Top() { return position.y - size.y / 2.f; }
    float Bottom() { return position.y + size.y / 2.f; }

    Vector2 position;
    Vector2 size;

    Vector2 velocity;
    Vector2 acceleration;
};
}

#endif
