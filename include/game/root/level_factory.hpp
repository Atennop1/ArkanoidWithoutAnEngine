#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_LEVEL_FACTORY_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_LEVEL_FACTORY_HPP_

#include "game/level/brick.hpp"
#include "game/level/brick_type.hpp"
#include "tools/shared_pointer.hpp"
#include "engine/physics/physics_simulation.hpp"
#include <vector>

namespace arkanoid
{
class LevelFactory
{
public:
    explicit LevelFactory(PhysicsSimulation *physics_simulation);

    std::vector<std::vector<SharedPointer<Brick>>> CreateMap(const std::vector<std::vector<BrickType>> &layout);

private:
    const float level_offset_x_ = 15.0f;
    const float level_offset_y_ = 6.0f;

    const int brick_width_ = 15;
    const int brick_height_ = 7;

    PhysicsSimulation *physics_simulation_;
};
}

#endif
