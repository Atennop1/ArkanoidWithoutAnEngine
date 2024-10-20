#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LEVEL_LEVEL_HPP_

#include "level_view.hpp"
#include "level_map.hpp"
#include "game/loop/objects/game_loop_object.hpp"
#include "tools/shared_pointer.hpp"

namespace arkanoid
{
class Level : public IGameLoopObject
{
public:
    Level(const LevelMap &map, const SharedPointer<LevelView> &level_view);

    void Update(float delta) override;

private:
    const LevelMap &map_;
    const SharedPointer<LevelView> level_view_;
};
}

#endif
