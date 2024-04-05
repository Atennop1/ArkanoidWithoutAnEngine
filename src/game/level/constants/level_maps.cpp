#include "level_maps.hpp"
#include "level_layouts.hpp"

LevelMap LevelMaps::m_k_first_ = LevelMap(LevelLayouts::First());

LevelMap& LevelMaps::First()
{
    return m_k_first_;
}

