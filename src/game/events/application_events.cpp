#include "application_events.hpp"

void ApplicationEvents::Update(float delta)
{
    m_events_.clear();
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
        m_events_.push_back(event);
}

std::vector<SDL_Event*> ApplicationEvents::GetEventsOfType(std::vector<Uint32> types)
{
    auto result = std::vector<SDL_Event*> { };

    for (auto &event : m_events_)
        if (std::find_if(types.begin(), types.end(), [&](Uint32 type) { return event.type == type; }) != types.end())
            result.push_back(&event);

    return result;
}
