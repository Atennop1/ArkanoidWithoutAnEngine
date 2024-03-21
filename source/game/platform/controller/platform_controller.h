#ifndef ARKANOIDWITHOUTANENGINE_9018F63D28364B1EA40B6207254C414C
#define ARKANOIDWITHOUTANENGINE_9018F63D28364B1EA40B6207254C414C

#include "../../input/input.h"
#include "../../loop/updatables/updatable.h"
#include "../model/platform.h"

class PlatformController : public IUpdatable
{
private:
    const Input &m_input_;
    Platform &m_platform_;

    const float m_move_speed_ = 40.0f;

public:
    PlatformController(const Input &input, Platform &platform);
    ~PlatformController() override = default;

    void Update(float delta) override;
};

#endif
