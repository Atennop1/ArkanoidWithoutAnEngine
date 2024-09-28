#ifndef ARKANOIDWITHOUTANENGINE_C2386548878343C9A8A53CE01BA4B335
#define ARKANOIDWITHOUTANENGINE_C2386548878343C9A8A53CE01BA4B335

#include "read_only_game_time.hpp"

namespace arkanoid
{
    class IGameTime : public IReadOnlyGameTime
    {
    public:
        virtual void Activate() = 0;

        virtual void Deactivate() = 0;

        ~IGameTime() override = default;
    };
}

#endif
