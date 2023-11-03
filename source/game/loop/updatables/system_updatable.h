#pragma once
#include "SDL.h"

class ISystemUpdatable
{
public:
    virtual ~ISystemUpdatable() = default;
    virtual void Update(SDL_Event event) = 0;
};
