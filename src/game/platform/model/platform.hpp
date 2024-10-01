#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_MODEL_PLATFORM_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_MODEL_PLATFORM_HPP_

#include "../../loop/game_loop_object.hpp"
#include "../view/platform_view.hpp"
#include "Box2D.hpp"
#include "shared_pointer.hpp"

namespace arkanoid
{
    class Platform : public IGameLoopObject
    {
    private:
        box2d::Vector2 platform_position_ { };
        SharedPointer<PlatformView> platform_view_;

    public:
        explicit Platform(SharedPointer<PlatformView> &platform_view);
        ~Platform() override = default;

        void Update(float delta) override;
        void Move(box2d::Vector2 move_vector);
    };
}

#endif
