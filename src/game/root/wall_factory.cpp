#include "game/root/wall_factory.hpp"

namespace arkanoid
{
SharedPointer<Wall> WallFactory::CreateWall(const WindowReferences &window_references, const char *texture_file_path, PhysicalProperties physical_properties)
{
    auto wall_view = SharedPointer(new WallView(window_references, texture_file_path));
    auto wall = SharedPointer(new Wall(physical_properties, wall_view));
    return wall;
}
}