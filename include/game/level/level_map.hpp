#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_MAP_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_MAP_HPP_

#include <array>

namespace arkanoid
{
class LevelMap
{
public:
    LevelMap();
    explicit LevelMap(std::array<std::array<char, 12>, 14> &map);

    std::array<char, 12> operator[](int index) const;

private:
    const std::array<std::array<char, 12>, 14> &map_;
};
}

#endif
