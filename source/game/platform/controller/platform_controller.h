#pragma once

#include "../../input/input.h"
#include "../../loop/updatable.h"
#include "../model/platform.h"

class PlatformController : IUpdatable
{
private:
    Input &m_input_;
    Platform &m_platform_;

    const float m_move_speed_ = 40.0f;

public:
    PlatformController(const Input &input, const Platform &platform);
    ~PlatformController() override = default;

    void Update(float delta) override;
};
