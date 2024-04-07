#ifndef ARKANOIDWITHOUTANENGINE_2FC43BECA40A4F5FB108D9E5358A99D0
#define ARKANOIDWITHOUTANENGINE_2FC43BECA40A4F5FB108D9E5358A99D0

#include "../map/level_map.hpp"
#include <array>

class LevelMaps
{
private:
    static LevelMap m_k_first_;

public:
    static LevelMap& First();
};

#endif
