#ifndef ARKANOIDWITHOUTANENGINE_8ACABEDE0DD949F088DEEF065A95DA26
#define ARKANOIDWITHOUTANENGINE_8ACABEDE0DD949F088DEEF065A95DA26

#include "SDL.h"

class IEventsUpdatable
{
public:
    virtual ~IEventsUpdatable() = default;
    virtual void Update(const SDL_Event &event) = 0;
};

#endif
