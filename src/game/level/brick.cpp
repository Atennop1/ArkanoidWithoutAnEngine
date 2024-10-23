#include "game/level/brick.hpp"

namespace arkanoid
{
Brick::Brick(PhysicalProperties properties, BrickType type)
    : IGameObject(properties), type_(type) { }
}