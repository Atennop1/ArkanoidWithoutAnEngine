#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_CONTROLLER_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_CONTROLLER_HPP_

#include "platform.hpp"
#include "engine/events/input/input.hpp"

namespace arkanoid
{
class PlatformController : public IGameLoopObject
{
public:
    PlatformController(SharedPointer<Platform> &platform, const SharedPointer<Input> &input);

    void Update(float delta) override;

private:
    const float move_speed_ = 80.0f;

    SharedPointer<Platform> platform_;
    const SharedPointer<Input> input_;
};
}

#endif
