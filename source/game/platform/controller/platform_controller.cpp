﻿#include "platform_controller.h"

//----------------------------------------------------------------------------------------------------
PlatformController::PlatformController(Input *input, Platform *platform)
{
    m_input_ = input;
    m_platform_ = platform;
}

//----------------------------------------------------------------------------------------------------
PlatformController::~PlatformController()
{
    free(m_input_);
    free(m_platform_);
}

//----------------------------------------------------------------------------------------------------
void PlatformController::Update(float delta)
{
    const bool is_left_key_pressed = m_input_->IsKeyPressed(kLeft);
    const bool is_right_key_pressed = m_input_->IsKeyPressed(kRight);

    if (is_left_key_pressed ^ is_right_key_pressed)
        m_platform_->Move(Vector2(m_move_speed_ * (is_left_key_pressed ? -1.0f : 1.0f) * delta, 0.0f));
}

//----------------------------------------------------------------------------------------------------
