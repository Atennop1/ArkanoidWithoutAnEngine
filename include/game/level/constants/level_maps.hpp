#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_CONSTANTS_LEVEL_MAPS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_CONSTANTS_LEVEL_MAPS_HPP_

#include "game/level/level_map.hpp"
#include <array>

namespace arkanoid
{
class LevelMaps
{
public:
    static LevelMap &First() { return kFirst; }

private:
    static LevelMap kFirst;
};
}

#endif
