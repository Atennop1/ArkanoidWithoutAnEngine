#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_WALL_FACTORY_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_WALL_FACTORY_HPP_

#include "game/wall/wall.hpp"

namespace arkanoid
{
class WallFactory
{
public:
    SharedPointer<Wall> CreateWall(const WindowReferences &window_references, const char *texture_file_path, PhysicalProperties physical_properties);
};
}

#endif
