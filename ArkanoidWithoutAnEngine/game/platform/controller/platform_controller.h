#pragma once

#include "../../input/input.h"
#include "../../loop/updatables/updatable.h"
#include "../model/platform.h"

class PlatformController : IUpdatable
{
private:
    Input *m_input_;
    Platform *m_platform_;

    const int m_move_force_ = 5;

public:
    PlatformController(Input *input, Platform *platform);
    ~PlatformController() override;

    void Update(float delta) override;
};
