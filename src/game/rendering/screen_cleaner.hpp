#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_RENDERING_SCREEN_CLEANER_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_RENDERING_SCREEN_CLEANER_HPP_

#include "window_references/window_references.hpp"
#include "../loop/objects/game_loop_object.hpp"

namespace arkanoid
{
class ScreenCleaner : public IGameLoopObject
{
private:
    const WindowReferences &window_references_;

public:
    explicit ScreenCleaner(const WindowReferences &window_references);
    ~ScreenCleaner() override = default;

    void Update(float delta) override;
};
}

#endif
