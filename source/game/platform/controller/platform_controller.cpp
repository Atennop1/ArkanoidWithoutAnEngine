#include "platform_controller.h"

PlatformController::PlatformController(const Input &input, const Platform &platform)
    : m_input_(const_cast<Input&>(input)), m_platform_(const_cast<Platform&>(platform)) { }

void PlatformController::Update(float delta)
{
    const bool is_left_key_pressed = m_input_.IsKeyPressed(kLeft);
    const bool is_right_key_pressed = m_input_.IsKeyPressed(kRight);

    if (is_left_key_pressed ^ is_right_key_pressed)
        m_platform_.Move(Vector2(m_move_speed_ * (is_left_key_pressed ? -1.0f : 1.0f) * delta, 0.0f));
}
