#ifndef ARKANOIDWITHOUTANENGINE_B8E5742E42264A16AD64095AC06A4333
#define ARKANOIDWITHOUTANENGINE_B8E5742E42264A16AD64095AC06A4333

#include "../../loop/game_loop_object.hpp"
#include "../model/platform.hpp"
#include "../../events/input/input.hpp"
#include "shared_pointer.hpp"

class PlatformController : public IGameLoopObject
{
private:
    SharedPointer<Platform> m_platform_;
    const SharedPointer<Input> m_input_;

    const float m_move_speed_ = 40.0f;

public:
    PlatformController(SharedPointer<Platform> &platform, const SharedPointer<Input> &input);
    ~PlatformController() override = default;

    void Update(float delta) override;
};

#endif
