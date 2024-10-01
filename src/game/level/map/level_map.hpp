#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_MAP_LEVEL_MAP_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_MAP_LEVEL_MAP_HPP_

#include <array>

namespace arkanoid
{
    class LevelMap
    {
    private:
        const std::array<std::array<char, 12>, 14> &map_;

    public:
        LevelMap();
        explicit LevelMap(std::array<std::array<char, 12>, 14> &map);

        std::array<char, 12> operator[](int index) const;
    };
}

#endif
