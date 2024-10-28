#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_HPP_

#include "level_view.hpp"
#include "brick.hpp"
#include "tools/shared_pointer.hpp"
#include <vector>

namespace arkanoid
{
class Level : public IGameLoopObject
{
public:
    Level(const std::vector<std::vector<SharedPointer<Brick>>> &map, const SharedPointer<LevelView> &level_view);

    void Update(float delta) override;

private:
    std::vector<std::vector<SharedPointer<Brick>>> map_;
    const SharedPointer<LevelView> level_view_;
};
}

#endif
