#pragma once

#include "SDL.h"

class IEventsUpdatable
{
public:
    virtual ~IEventsUpdatable() = default;
    virtual void Update(const SDL_Event &event) = 0;
};