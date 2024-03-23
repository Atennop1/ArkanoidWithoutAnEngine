#ifndef ARKANOIDWITHOUTANENGINE_9018F63D28364B1EA40B6207254C414C
#define ARKANOIDWITHOUTANENGINE_9018F63D28364B1EA40B6207254C414C

#include <memory>
#include "../../input/input.h"
#include "../../loop/updatables/updatable.h"
#include "../model/platform.h"

class PlatformController : public IUpdatable
{
private:
    std::shared_ptr<Input> m_input_;
    std::unique_ptr<Platform> m_platform_;

    const float m_move_speed_ = 40.0f;

public:
    PlatformController(const std::shared_ptr<Input> &input, std::unique_ptr<Platform> &platform);
    ~PlatformController() override = default;

    void Update(float delta) override;
};

#endif
