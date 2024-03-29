#ifndef ARKANOIDWITHOUTANENGINE_FA27939454C14A05BF7D4DDD3EF88C1A
#define ARKANOIDWITHOUTANENGINE_FA27939454C14A05BF7D4DDD3EF88C1A

#include "read_only_game_time.h"

class IGameTime : public IReadOnlyGameTime
{
public:
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    ~IGameTime() override = default;
};

#endif
