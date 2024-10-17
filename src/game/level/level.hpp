#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_LEVEL_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LEVEL_LEVEL_HPP_

#include "../rendering/window_references/window_references.hpp"
#include "view/level_view.hpp"
#include "map/level_map.hpp"
#include "../loop/objects/game_loop_object.hpp"
#include "shared_pointer.hpp"

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
