#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_WALL_FACTORY_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_WALL_FACTORY_HPP_

#include "game/wall/wall.hpp"
#include <genesis/loop/game_loop.hpp>
#include <genesis/physics/physics_simulation.hpp>
#include <genesis/rendering/window_references.hpp>

namespace arkanoid
{
class WallFactory
{
public:
    WallFactory(genesis::GameLoop *game_loop, genesis::PhysicsSimulation *physics_simulation);

    genesis::SharedPointer<Wall> Create(const genesis::WindowReferences &window_references, const char *texture_file_path, genesis::PhysicalProperties physical_properties);

private:
    genesis::GameLoop *game_loop_;
    genesis::PhysicsSimulation *physics_simulation_;
};
}

#endif
