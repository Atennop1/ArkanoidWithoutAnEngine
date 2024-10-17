#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_CONSTANTS_LEVEL_MAPS_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_CONSTANTS_LEVEL_MAPS_HPP_

#include "../map/level_map.hpp"
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
