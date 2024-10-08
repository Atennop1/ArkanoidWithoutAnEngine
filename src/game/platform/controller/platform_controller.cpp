﻿#include "platform_controller.hpp"

arkanoid::PlatformController::PlatformController(SharedPointer<Platform> &platform, const SharedPointer<Input> &input)
    : input_(input), platform_(platform) { }

void arkanoid::PlatformController::Update(float delta)
{
    const bool kIsLeftKeyPressed = input_->IsKeyPressed(kLeft);
    const bool kIsRightKeyPressed = input_->IsKeyPressed(kRight);

    if (kIsLeftKeyPressed ^ kIsRightKeyPressed)
        platform_->Move(arkanoid::Vector2(move_speed_ * (kIsLeftKeyPressed ? -1.0f : 1.0f) * delta, 0.0f));
}
