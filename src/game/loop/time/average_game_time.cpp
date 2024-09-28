#include "average_game_time.hpp"
#include "SDL.h"

arkanoid::AverageGameTime::AverageGameTime()
{
    m_last_time_ = SDL_GetPerformanceCounter();
}

float arkanoid::AverageGameTime::Delta()
{
    float delta = (float)(SDL_GetPerformanceCounter() - m_last_time_) / (float)SDL_GetPerformanceFrequency(); // in seconds
    m_last_time_ = SDL_GetPerformanceCounter();
    return delta;
}
