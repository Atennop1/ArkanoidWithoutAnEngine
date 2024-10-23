#include "game/level/level_layouts.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"

namespace arkanoid
{
using BT = BrickType;

std::vector<std::vector<BrickType>> LevelLayouts::kEmpty = std::vector<std::vector<BrickType>>
{
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
     { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
};

std::vector<std::vector<BrickType>> LevelLayouts::kFirst = std::vector<std::vector<BrickType>>
{
    { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
    { BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet },
    { BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet },
    { BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue },
    { BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue },
    { BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet },
    { BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet, BT::kViolet },
    { BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue },
    { BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue, BT::kBlue },
    { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
    { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
    { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
    { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
    { BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone, BT::kNone },
};
}

#pragma clang diagnostic pop