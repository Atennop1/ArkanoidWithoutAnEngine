#pragma once
#include "../input/input.h"
#include "model/platform.h"

class PlatformController
{
private:
    Input *m_input_;
    Platform *m_platform_;

public:
    PlatformController(Input *input, Platform *platform);
};
