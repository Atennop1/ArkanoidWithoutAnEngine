#ifndef ARKANOIDWITHOUTANENGINE_AVERAGE_GAME_TIME_H
#define ARKANOIDWITHOUTANENGINE_AVERAGE_GAME_TIME_H

#include "game_time.h"

class AverageGameTime : public IGameTime
{
private:
    unsigned long long m_last_time_;

public:
    float Delta() override;

    void Activate() override;
    void Deactivate() override;
};


#endif
