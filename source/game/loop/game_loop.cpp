#include <algorithm>
#include <stdexcept>
#include "game_loop.h"
#include "SDL.h"

GameLoop::GameLoop(IReadOnlyGameTime &game_time, const std::list<IUpdatable*> &updatables, const std::list<IEventsUpdatable*> &events_updatables)
    : m_game_time_(game_time), m_updatables_(updatables), m_events_updatables_(events_updatables) { }

GameLoop::~GameLoop()
{
    for (IUpdatable* updatable : m_updatables_)
        free(updatable);

    for (IEventsUpdatable* updatable : m_events_updatables_)
        free(updatable);
}

void GameLoop::AddUpdatable(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) != m_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.push_back(updatable);
}

void GameLoop::RemoveUpdatable(const IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) == m_updatables_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    std::remove(m_updatables_.begin(), m_updatables_.end(), updatable);
}

void GameLoop::AddEventsUpdatable(IEventsUpdatable *updatable)
{
    if (std::find(m_events_updatables_.begin(), m_events_updatables_.end(), updatable) != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable already in loop");

    m_events_updatables_.push_back(updatable);
}

void GameLoop::RemoveEventsUpdatable(const IEventsUpdatable *updatable)
{
    if (std::find(m_events_updatables_.begin(), m_events_updatables_.end(), updatable) == m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable doesn't in loop");

    std::remove(m_events_updatables_.begin(), m_events_updatables_.end(), updatable);
}

void GameLoop::Activate() const
{
    SDL_Event event;
    float delta;

    while (true)
    {
        if (!m_game_time_.IsActive)
            continue;

        delta = m_game_time_.Delta();
        while (SDL_PollEvent(&event) != 0)
            for (IEventsUpdatable *updatable: m_events_updatables_)
                updatable->Update(event);

        for (IUpdatable *updatable : m_updatables_)
            updatable->Update(delta);

        if (event.type == SDL_QUIT)
            break;
    }
}
