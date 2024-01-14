#ifndef ARKANOIDWITHOUTANENGINE_GAME_TIME_H
#define ARKANOIDWITHOUTANENGINE_GAME_TIME_H

#include "read_only_game_time.h"

class IGameTime : public IReadOnlyGameTime
{
public:
    ~IGameTime() override = default;
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
};

#endif
