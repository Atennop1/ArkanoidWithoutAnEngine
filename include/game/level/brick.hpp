#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_BRICK_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_BRICK_HPP_

#include "brick_type.hpp"
#include <genesis/loop/objects/game_object.hpp>

namespace arkanoid
{
class Brick : public genesis::IGameObject
{
public:
    Brick(genesis::PhysicalProperties properties, BrickType type);

    BrickType Type() { return type_; }

private:
    BrickType type_;
};
}

#endif
