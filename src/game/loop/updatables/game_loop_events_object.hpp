#ifndef ARKANOIDWITHOUTANENGINE_AF97988956854AE3B1314472FAEBB8AA
#define ARKANOIDWITHOUTANENGINE_AF97988956854AE3B1314472FAEBB8AA

#include "SDL.h"

class IGameLoopEventsObject
{
public:
    virtual ~IGameLoopEventsObject() = default;
    virtual void Update(const SDL_Event &event) = 0;
};

#endif
