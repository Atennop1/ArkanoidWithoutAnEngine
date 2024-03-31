#include "average_game_time.hpp"
#include "SDL.h"

bool AverageGameTime::IsActive()
{
    return is_active;
}

void AverageGameTime::Activate()
{
    is_active = true;
}

void AverageGameTime::Deactivate()
{
    is_active = false;
}

float AverageGameTime::Delta()
{
    float delta = (float)(SDL_GetPerformanceCounter() - m_last_time_) / (float)SDL_GetPerformanceFrequency(); // in seconds
    m_last_time_ = SDL_GetPerformanceCounter();
    return delta;
}
