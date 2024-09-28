#ifndef ARKANOIDWITHOUTANENGINE_E5C974F2C9AF47968137649F9460EC9F
#define ARKANOIDWITHOUTANENGINE_E5C974F2C9AF47968137649F9460EC9F

#include <array>

namespace arkanoid
{
    class LevelMap
    {
    private:
        const std::array<std::array<char, 12>, 14> &m_map_;

    public:
        LevelMap();

        explicit LevelMap(std::array<std::array<char, 12>, 14> &map);

        std::array<char, 12> operator[](int index) const;
    };
}

#endif
