#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_RENDERING_SCREEN_APPLIER_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_RENDERING_SCREEN_APPLIER_HPP_

#include "window_references/window_references.hpp"
#include "../loop/objects/game_loop_object.hpp"

namespace arkanoid
{
    class ScreenApplier : public IGameLoopObject
    {
    private:
        const WindowReferences &window_references_;

    public:
        explicit ScreenApplier(const WindowReferences &window_references);
        ~ScreenApplier() override = default;

        void Update(float delta) override;
    };
}

#endif
