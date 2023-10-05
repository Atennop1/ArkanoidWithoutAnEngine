#pragma once
#include "../../input/input.h"
#include "../model/platform.h"

class PlatformController : IUpdatable
{
private:
    Input *m_input_;
    Platform *m_platform_;

    const int m_move_force = 5;

public:
    PlatformController(Input *input, Platform *platform);
    ~PlatformController() override;

    void Update(float delta) override;
};
