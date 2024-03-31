#include "platform_controller.hpp"

PlatformController::PlatformController(const std::shared_ptr<Input> &input, std::unique_ptr<Platform> &platform)
    : m_input_(input), m_platform_(std::move(platform)) { }

void PlatformController::Update(float delta)
{
    const bool is_left_key_pressed = m_input_->IsKeyPressed(kLeft);
    const bool is_right_key_pressed = m_input_->IsKeyPressed(kRight);

    if (is_left_key_pressed ^ is_right_key_pressed)
        m_platform_->Move(Box2D::Vec2(m_move_speed_ * (is_left_key_pressed ? -1.0f : 1.0f) * delta, 0.0f));
}
