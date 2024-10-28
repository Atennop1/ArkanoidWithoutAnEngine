#include "game/root/wall_factory.hpp"

namespace arkanoid
{
WallFactory::WallFactory(GameLoop *game_loop, PhysicsSimulation *physics_simulation)
    : game_loop_(game_loop), physics_simulation_(physics_simulation) { }

SharedPointer<Wall> WallFactory::Create(const WindowReferences &window_references, const char *texture_file_path, PhysicalProperties physical_properties)
{
    auto wall_view = SharedPointer(new WallView(window_references, texture_file_path));
    auto wall = SharedPointer(new Wall(physical_properties, wall_view));

    game_loop_->Add(wall);
    physics_simulation_->Add(wall);
    return wall;
}
}