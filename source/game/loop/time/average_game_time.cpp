#include "average_game_time.h"
#include "SDL.h"

void AverageGameTime::Activate()
{
    IsActive = true;
}

void AverageGameTime::Deactivate()
{
    IsActive = false;
}

float AverageGameTime::Delta()
{
    float delta = (float)(SDL_GetPerformanceCounter() - m_last_time_) / (float)SDL_GetPerformanceFrequency(); // in seconds
    m_last_time_ = SDL_GetPerformanceCounter();
    return delta;
}
