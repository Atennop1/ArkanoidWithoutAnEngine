#ifndef ARKANOIDWITHOUTANENGINE_EBCF46318AB44062AAB0CE7E37310335
#define ARKANOIDWITHOUTANENGINE_EBCF46318AB44062AAB0CE7E37310335

#include "game_time.h"

class AverageGameTime : public IGameTime
{
private:
    bool is_active;
    unsigned long long m_last_time_;

public:
    bool IsActive() override;
    float Delta() override;

    void Activate() override;
    void Deactivate() override;
};

#endif
