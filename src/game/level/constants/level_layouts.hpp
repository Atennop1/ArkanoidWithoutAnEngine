#ifndef ARKANOIDWITHOUTANENGINE_F8506D4BBA994BABBA9D8E414158DDDA
#define ARKANOIDWITHOUTANENGINE_F8506D4BBA994BABBA9D8E414158DDDA

#include <array>

class LevelLayouts
{
private:
    static std::array<std::array<char, 12>, 14> m_empty_;
    static std::array<std::array<char, 12>, 14> m_k_first_;

public:
    static std::array<std::array<char, 12>, 14>& Empty();
    static std::array<std::array<char, 12>, 14>& First();
};

#endif