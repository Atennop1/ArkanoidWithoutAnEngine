#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_BRICK_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_BRICK_HPP_

#include "brick_type.hpp"
#include "engine/loop/objects/game_object.hpp"

namespace arkanoid
{
class Brick : public IGameObject
{
public:
    Brick(PhysicalProperties properties, BrickType type);

    BrickType Type() { return type_; }

private:
    BrickType type_;
};
}

#endif
