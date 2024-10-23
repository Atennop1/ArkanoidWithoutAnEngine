#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_BRICK_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_BRICK_HPP_

#include "game/loop/objects/game_object.hpp"
#include "brick_type.hpp"

namespace arkanoid
{
class Brick : public IGameObject
{
public:
    Brick(PhysicalProperties properties, BrickType type);

    void Destroy() { is_destroyed_ = true; }
    bool IsDestroyed() { return is_destroyed_; }
    BrickType Type() { return type_; }

private:
    BrickType type_;
    bool is_destroyed_ = false;
};
}

#endif
