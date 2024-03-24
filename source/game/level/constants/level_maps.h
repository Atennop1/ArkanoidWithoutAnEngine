#ifndef ARKANOIDWITHOUTANENGINE_F1BF0972DB3E46EA959AB3EE8FE9DF13
#define ARKANOIDWITHOUTANENGINE_F1BF0972DB3E46EA959AB3EE8FE9DF13

#include <array>
#include <memory>
#include "../map/level_map.h"

class LevelMaps
{
private:
    static std::unique_ptr<LevelMap> kFirst;

public:
    static std::unique_ptr<LevelMap>& First();
};

#endif
