#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_TIME_GAME_TIME_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_TIME_GAME_TIME_HPP_

#include "read_only_game_time.hpp"

namespace arkanoid
{
    class IGameTime : public IReadOnlyGameTime
    {
    public:
        ~IGameTime() override = default;

        virtual void Activate() = 0;
        virtual void Deactivate() = 0;
    };
}

#endif
