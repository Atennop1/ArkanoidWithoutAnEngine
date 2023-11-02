#pragma once

class ISystemUpdatable
{
public:
    virtual ~ISystemUpdatable() = default;
    virtual void Update(SDL_Event event) = 0;
};
