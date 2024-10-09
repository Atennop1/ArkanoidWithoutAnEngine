#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_CONSTANTS_LEVEL_LAYOUTS_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_CONSTANTS_LEVEL_LAYOUTS_HPP_

#include <array>

namespace arkanoid
{
class LevelLayouts
{
private:
    static std::array<std::array<char, 12>, 14> kEmpty;
    static std::array<std::array<char, 12>, 14> kFirst;

public:
    static std::array<std::array<char, 12>, 14> &Empty() { return kEmpty; }
    static std::array<std::array<char, 12>, 14> &First() { return kFirst; }
};
}

#endif
