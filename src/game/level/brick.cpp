#include "game/level/brick.hpp"

namespace arkanoid
{
Brick::Brick(genesis::PhysicalProperties properties, BrickType type)
    : IGameObject(properties), type_(type) { }
}