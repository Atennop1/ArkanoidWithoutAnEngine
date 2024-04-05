#include <stdexcept>
#include "game_logic_loop.hpp"
#include "SDL.h"

GameLogicLoop::GameLogicLoop(IReadOnlyGameTime &game_time)
    : m_game_time_(game_time) { }

void GameLogicLoop::Update()
{
    if (!m_game_time_.IsActive() || !IsActive())
        return;

    SDL_Event event;
    float delta = m_game_time_.Delta();

    while (SDL_PollEvent(&event) != 0)
    {
        for (const auto &updatable: m_events_updatables_)
            updatable->Update(event);

        if (event.type == SDL_QUIT)
            m_is_active_ = false;
    }

    for (const auto &updatable: m_updatables_)
        updatable->Update(delta);
}

void GameLogicLoop::AddUpdatable(IUpdatable &updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), &updatable) != m_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.push_back(&updatable);
}


void GameLogicLoop::RemoveUpdatable(const IUpdatable &updatable)
{
    auto find_iterator = std::find(m_updatables_.begin(), m_updatables_.end(), &updatable);

    if (find_iterator != m_updatables_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_updatables_.erase(find_iterator);
}

void GameLogicLoop::AddEventsUpdatable(IEventsUpdatable &updatable)
{
    if (std::find(m_events_updatables_.begin(), m_events_updatables_.end(), &updatable) != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable already in loop");

    m_events_updatables_.push_back(&updatable);
}

void GameLogicLoop::RemoveEventsUpdatable(const IEventsUpdatable &updatable)
{
    auto find_iterator = std::find(m_events_updatables_.begin(), m_events_updatables_.end(), &updatable);

    if (find_iterator != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable doesn't in loop");

    m_events_updatables_.erase(find_iterator);
}
