#ifndef ARKANOIDWITHOUTANENGINE_FA03B776089F4A33A1D8349D9B34A36B
#define ARKANOIDWITHOUTANENGINE_FA03B776089F4A33A1D8349D9B34A36B

#include <array>
#include <memory>
#include "../map/level_map.h"

class Levels
{
private:
    static std::unique_ptr<LevelMap> kFirst;

public:
    static std::unique_ptr<LevelMap>& First();
};

#endif
