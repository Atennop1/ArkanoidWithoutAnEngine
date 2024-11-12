#include "game/root/wall_factory.hpp"

namespace arkanoid
{
WallFactory::WallFactory(genesis::GameLoop *game_loop, genesis::PhysicsSimulation *physics_simulation)
    : game_loop_(game_loop), physics_simulation_(physics_simulation) { }

genesis::SharedPointer<Wall> WallFactory::Create(const genesis::WindowReferences &window_references, const char *texture_file_path, genesis::PhysicalProperties physical_properties)
{
    auto wall_view = genesis::SharedPointer(new WallView(window_references, texture_file_path));
    auto wall = genesis::SharedPointer(new Wall(physical_properties, wall_view));

    game_loop_->Add(wall);
    physics_simulation_->Add(wall);
    return wall;
}
}