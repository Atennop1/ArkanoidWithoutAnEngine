#ifndef ARKANOIDWITHOUTANENGINE_B180C9D1E1ED4AE4893F8F5CCFEE6662
#define ARKANOIDWITHOUTANENGINE_B180C9D1E1ED4AE4893F8F5CCFEE6662

#include "game_time.hpp"

class AverageGameTime : public IGameTime
{
private:
    bool m_is_active_ = true;
    unsigned long long m_last_time_;

public:
    AverageGameTime();
    bool IsActive() override { return m_is_active_; }
    float Delta() override;

    void Activate() override { m_is_active_ = true; }
    void Deactivate() override { m_is_active_ = false; }
};

#endif
