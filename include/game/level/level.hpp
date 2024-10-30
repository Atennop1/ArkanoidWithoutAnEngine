#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_HPP_

#include "level_view.hpp"
#include "brick.hpp"
#include <vector>
#include <genesis/memory/shared_pointer.hpp>

namespace arkanoid
{
class Level : public genesis::IGameLoopObject
{
public:
    Level(const std::vector<std::vector<genesis::SharedPointer<Brick>>> &map, genesis::SharedPointer<LevelView> level_view);

    void Update(float delta) override;

private:
    std::vector<std::vector<genesis::SharedPointer<Brick>>> map_;
    genesis::SharedPointer<LevelView> level_view_;
};
}

#endif
