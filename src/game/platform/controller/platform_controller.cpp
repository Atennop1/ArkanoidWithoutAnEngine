#include "platform_controller.hpp"

arkanoid::PlatformController::PlatformController(SharedPointer<Platform> &platform, const SharedPointer<Input> &input)
    : m_input_(input), m_platform_(platform) { }

void arkanoid::PlatformController::Update(float delta)
{
    const bool is_left_key_pressed = m_input_->IsKeyPressed(KLeft);
    const bool is_right_key_pressed = m_input_->IsKeyPressed(KRight);

    if (is_left_key_pressed ^ is_right_key_pressed)
        m_platform_->Move(box2d::Vector2(m_move_speed_ * (is_left_key_pressed ? -1.0f : 1.0f) * delta, 0.0f));
}
