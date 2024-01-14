#ifndef ARKANOIDWITHOUTANENGINE_READ_ONLY_GAME_TIME_H
#define ARKANOIDWITHOUTANENGINE_READ_ONLY_GAME_TIME_H

class IReadOnlyGameTime
{
public:
    virtual ~IReadOnlyGameTime() = default;
    virtual float Delta() = 0;
    bool IsActive = true;
};

#endif
