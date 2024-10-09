#include "average_game_time.hpp"
#include "SDL.h"

namespace arkanoid
{
AverageGameTime::AverageGameTime()
{
    last_time_ = SDL_GetPerformanceCounter();
}

float AverageGameTime::Delta()
{
    float delta = (float)(SDL_GetPerformanceCounter() - last_time_) / (float)SDL_GetPerformanceFrequency(); // in seconds
    last_time_ = SDL_GetPerformanceCounter();
    return delta;
}
}
