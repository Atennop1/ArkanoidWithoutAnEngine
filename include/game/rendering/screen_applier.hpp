#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_RENDERING_SCREEN_APPLIER_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_RENDERING_SCREEN_APPLIER_HPP_

#include "window_references.hpp"
#include "game/loop/objects/game_loop_object.hpp"

namespace arkanoid
{
class ScreenApplier : public IGameLoopObject
{
public:
    explicit ScreenApplier(const WindowReferences &window_references);

    void Update(float delta) override;

private:
    const WindowReferences &window_references_;
};
}

#endif
