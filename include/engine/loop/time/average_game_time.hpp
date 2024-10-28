#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_TIME_AVERAGE_GAME_TIME_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_LOOP_TIME_AVERAGE_GAME_TIME_HPP_

#include "game_time.hpp"

namespace arkanoid
{
class AverageGameTime : public IGameTime
{
public:
    AverageGameTime();

    float Delta() override;
    bool IsActive() override { return is_active_; }

    void Activate() override { is_active_ = true; }
    void Deactivate() override { is_active_ = false; }

private:
    bool is_active_ = true;
    unsigned long long last_time_;
};
}

#endif
