#ifndef ARKANOIDWITHOUTANENGINE_B180C9D1E1ED4AE4893F8F5CCFEE6662
#define ARKANOIDWITHOUTANENGINE_B180C9D1E1ED4AE4893F8F5CCFEE6662

#include "game_time.hpp"

class AverageGameTime : public IGameTime
{
private:
    bool is_active = true;
    unsigned long long m_last_time_;

public:
    bool IsActive() override;
    float Delta() override;

    void Activate() override;
    void Deactivate() override;
};

#endif
