#include "application_events.hpp"
#include <algorithm>

void arkanoid::ApplicationEvents::Update(float delta)
{
    events_.clear();
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
        events_.push_back(event);
}

std::vector<SDL_Event*> arkanoid::ApplicationEvents::GetEventsOfType(std::vector<Uint32> types)
{
    auto result = std::vector<SDL_Event*> { };

    for (auto &event : events_)
        if (std::ranges::find_if(types.begin(), types.end(), [&](Uint32 type) { return event.type == type; }) != types.end())
            result.push_back(&event);

    return result;
}
