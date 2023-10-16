#pragma once

#include "../../input/input.h"
#include "../../loop/updatables/updatable.h"
#include "../model/platform.h"

class PlatformController : IUpdatable
{
private:
    Input *m_input_;
    Platform *m_platform_;

    const float m_move_speed_ = 20.0f;

public:
    PlatformController(Input *input, Platform *platform);
    ~PlatformController() override;

    void Update(float delta) override;
};
