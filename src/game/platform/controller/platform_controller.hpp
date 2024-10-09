#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_CONTROLLER_PLATFORM_CONTROLLER_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_CONTROLLER_PLATFORM_CONTROLLER_HPP_

#include "../../loop/objects/game_loop_object.hpp"
#include "../model/platform.hpp"
#include "../../events/input/input.hpp"
#include "shared_pointer.hpp"

namespace arkanoid
{
class PlatformController : public IGameLoopObject
{
private:
    SharedPointer<Platform> platform_;
    const SharedPointer<Input> input_;

    const float move_speed_ = 40.0f;

public:
    PlatformController(SharedPointer<Platform> &platform, const SharedPointer<Input> &input);
    ~PlatformController() override = default;

    void Update(float delta) override;
};
}

#endif
