#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_LAYOUTS_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_LAYOUTS_HPP_

#include <vector>
#include "game/level/brick_type.hpp"

namespace arkanoid
{
class LevelLayouts
{
public:
    static std::vector<std::vector<BrickType>> &Empty() { return kEmpty; }
    static std::vector<std::vector<BrickType>> &First() { return kFirst; }

private:
    static std::vector<std::vector<BrickType>> kEmpty;
    static std::vector<std::vector<BrickType>> kFirst;

};
}

#endif
