#ifndef ARKANOIDWITHOUTANENGINE_506283DE7D15404A95B547A7EEC5925C
#define ARKANOIDWITHOUTANENGINE_506283DE7D15404A95B547A7EEC5925C

#include "SDL.h"

class IEventsUpdatable
{
public:
    virtual ~IEventsUpdatable() = default;
    virtual void Update(const SDL_Event &event) = 0;
};

#endif
