#include "game/platform/platform_controller.hpp"

namespace arkanoid
{
PlatformController::PlatformController(SharedPointer<Platform> &platform, const SharedPointer<Input> &input)
    : input_(input), platform_(platform) { }

void PlatformController::Update(float delta)
{
    const bool kIsLeftKeyPressed = input_->IsKeyPressed(KeyType::kLeft);
    const bool kIsRightKeyPressed = input_->IsKeyPressed(KeyType::kRight);

    if (kIsLeftKeyPressed ^ kIsRightKeyPressed)
        platform_->Move(Vector2(move_speed_ * (kIsLeftKeyPressed ? -1.0f : 1.0f) * delta, 0.0f));
}
}
