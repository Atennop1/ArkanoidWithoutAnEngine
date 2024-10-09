#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_TIME_READ_ONLY_GAME_TIME_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_TIME_READ_ONLY_GAME_TIME_HPP_

namespace arkanoid
{
class IReadOnlyGameTime
{
public:
    virtual ~IReadOnlyGameTime() = default;

    virtual bool IsActive() = 0;
    virtual float Delta() = 0;
};
}

#endif
