#include "game/platform/platform_controller.hpp"
#include "SDL2/SDL.h"

namespace arkanoid
{
PlatformController::PlatformController(genesis::SharedPointer<Platform> &platform, genesis::SharedPointer<genesis::Input> input)
    : input_(input), platform_(platform) { }

void PlatformController::Update(float delta)
{
    const bool kIsLeftKeyPressed = input_->IsKeyPressed(SDLK_LEFT) || input_->IsKeyPressed(SDLK_a);
    const bool kIsRightKeyPressed = input_->IsKeyPressed(SDLK_RIGHT) || input_->IsKeyPressed(SDLK_d);

    if (kIsLeftKeyPressed ^ kIsRightKeyPressed)
        platform_->Move(genesis::Vector2(move_speed_ * (kIsLeftKeyPressed ? -1.0f : 1.0f) * delta, 0.0f));
}
}
