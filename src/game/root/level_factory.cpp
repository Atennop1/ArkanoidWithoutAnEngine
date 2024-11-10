#include "game/root/level_factory.hpp"

namespace arkanoid
{
LevelFactory::LevelFactory(genesis::PhysicsSimulation *physics_simulation)
    : physics_simulation_(physics_simulation) { }

std::vector<std::vector<genesis::SharedPointer<Brick>>> LevelFactory::CreateMap(const std::vector<std::vector<BrickType>> &layout)
{
    auto result = std::vector<std::vector<genesis::SharedPointer<Brick>>> { };

    for (int i = 0; i < layout.size(); i++)
    {
        result.push_back({ });
        for (int j = 0; j < layout[0].size(); j++)
        {
            if (layout[i][j] == BrickType::kNone)
                continue;

            auto position = genesis::Vector2(level_offset_x_ + (brick_width_ + 1.0f) * j, level_offset_y_ - (brick_height_ + 1.0f) * i);
            auto brick = genesis::SharedPointer(new Brick(genesis::PhysicalProperties { position, { float(brick_width_), float(brick_height_) }}, layout[i][j]));

            physics_simulation_->Add(brick);
            result[i].push_back(brick);
        }
    }

    return result;
}
}