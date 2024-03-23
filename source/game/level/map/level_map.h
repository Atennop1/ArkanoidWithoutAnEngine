#ifndef ARKANOIDWITHOUTANENGINE_B428AA02E93D4EA0A9EDA8951361A8F8
#define ARKANOIDWITHOUTANENGINE_B428AA02E93D4EA0A9EDA8951361A8F8

#include <array>
#include <memory>

class LevelMap
{
private:
    const std::unique_ptr<std::array<std::array<char, 12>, 14>> m_map_;

public:
    LevelMap();
    explicit LevelMap(std::unique_ptr<std::array<std::array<char, 12>, 14>> &&map);

    std::array<char, 12> operator[](int index) const;
};


#endif
