#include <algorithm>
#include <stdexcept>
#include "game_loop.h"
#include "SDL.h"

GameLoop::GameLoop(IReadOnlyGameTime &game_time)
        : m_game_time_(game_time), m_updatables_(), m_events_updatables_() { }

GameLoop::GameLoop(IReadOnlyGameTime &game_time, const std::vector<std::reference_wrapper<IUpdatable>> &updatables)
        : m_game_time_(game_time), m_updatables_(updatables), m_events_updatables_() { }

GameLoop::GameLoop(IReadOnlyGameTime &game_time, const std::vector<std::reference_wrapper<IUpdatable>> &updatables, const std::vector<std::reference_wrapper<IEventsUpdatable>> &events_updatables)
    : m_game_time_(game_time), m_updatables_(updatables), m_events_updatables_(events_updatables) { }

void GameLoop::AddUpdatable(IUpdatable &updatable)
{
    if (std::find_if(m_updatables_.begin(), m_updatables_.end(), [&](std::reference_wrapper<IUpdatable> &i) { return &i.get() == &updatable; }) != m_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.emplace_back(updatable);
}

void GameLoop::RemoveUpdatable(const IUpdatable &updatable)
{
    auto find_iterator = std::find_if(m_updatables_.begin(), m_updatables_.end(), [&](std::reference_wrapper<IUpdatable> &i) { return &i.get() == &updatable; });

    if (find_iterator != m_updatables_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_updatables_.erase(find_iterator);
}

void GameLoop::AddEventsUpdatable(IEventsUpdatable &updatable)
{
    if (std::find_if(m_events_updatables_.begin(), m_events_updatables_.end(), [&](std::reference_wrapper<IEventsUpdatable> &i) { return &i.get() == &updatable; }) != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable already in loop");

    m_events_updatables_.emplace_back(updatable);
}

void GameLoop::RemoveEventsUpdatable(const IEventsUpdatable &updatable)
{
    auto find_iterator = std::find_if(m_events_updatables_.begin(), m_events_updatables_.end(), [&](std::reference_wrapper<IEventsUpdatable> &i) { return &i.get() == &updatable; });

    if (find_iterator != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable doesn't in loop");

    m_events_updatables_.erase(find_iterator);
}

void GameLoop::Activate() const
{
    SDL_Event event;
    float delta;

    while (true)
    {
        if (!m_game_time_.IsActive())
            continue;

        delta = m_game_time_.Delta();
        while (SDL_PollEvent(&event) != 0)
            for (IEventsUpdatable &updatable: m_events_updatables_)
                updatable.Update(event);

        for (IUpdatable &updatable : m_updatables_)
            updatable.Update(delta);

        if (event.type == SDL_QUIT)
            break;
    }
}
