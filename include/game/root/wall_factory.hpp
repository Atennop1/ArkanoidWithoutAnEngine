#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_WALL_FACTORY_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_WALL_FACTORY_HPP_

#include "game/wall/wall.hpp"
#include "engine/physics/physics_simulation.hpp"
#include "engine/loop/game_loop.hpp"

namespace arkanoid
{
class WallFactory
{
public:
    WallFactory(GameLoop *game_loop, PhysicsSimulation *physics_simulation);

    SharedPointer<Wall> Create(const WindowReferences &window_references, const char *texture_file_path, PhysicalProperties physical_properties);

private:
    GameLoop *game_loop_;
    PhysicsSimulation *physics_simulation_;
};
}

#endif
