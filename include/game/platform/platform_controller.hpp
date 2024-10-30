#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_CONTROLLER_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_CONTROLLER_HPP_

#include "platform.hpp"
#include "genesis/events/input.hpp"

namespace arkanoid
{
class PlatformController : public genesis::IGameLoopObject
{
public:
    PlatformController(genesis::SharedPointer<Platform> &platform, genesis::SharedPointer<genesis::Input> input);

    void Update(float delta) override;

private:
    const float move_speed_ = 80.0f;

    genesis::SharedPointer<Platform> platform_;
    genesis::SharedPointer<genesis::Input> input_;
};
}

#endif
