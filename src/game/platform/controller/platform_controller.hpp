#ifndef ARKANOIDWITHOUTANENGINE_B8E5742E42264A16AD64095AC06A4333
#define ARKANOIDWITHOUTANENGINE_B8E5742E42264A16AD64095AC06A4333

#include <memory>
#include "../../input/input.hpp"
#include "../../loop/logic/updatables/updatable.hpp"
#include "../model/platform.hpp"

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
