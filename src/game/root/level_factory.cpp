#include "game/root/level_factory.hpp"

namespace arkanoid
{
std::vector<std::vector<SharedPointer<Brick>>> LevelFactory::MakeMap(const std::vector<std::vector<BrickType>> &layout, PhysicsSimulation *simulation)
{
    auto result = std::vector<std::vector<SharedPointer<Brick>>> { };

    for (int i = 0; i < layout.size(); i++)
    {
        result.push_back({ });
        for (int j = 0; j < layout[0].size(); j++)
        {
            if (layout[i][j] == BrickType::kNone)
                continue;

            auto position = Vector2(level_offset_x_ + (brick_width_ + 6.0f) * j, level_offset_y_ + (brick_height_ + 6.0f) * i);
            auto brick = SharedPointer(new Brick(PhysicalProperties { position, { float(brick_width_), float(brick_height_) }}, layout[i][j]));

            simulation->Add(brick);
            result[i].push_back(brick);
        }
    }

    return result;
}
}