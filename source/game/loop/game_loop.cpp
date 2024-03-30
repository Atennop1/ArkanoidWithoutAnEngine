﻿#include <algorithm>
#include <stdexcept>
#include "game_loop.h"
#include "SDL.h"

GameLoop::GameLoop(const std::shared_ptr<IReadOnlyGameTime> &game_time)
    : m_game_time_(game_time) { }

void GameLoop::Activate() const
{
    SDL_Event event;
    float delta;

    while (true)
    {
        if (!m_game_time_->IsActive())
            continue;

        delta = m_game_time_->Delta();
        while (SDL_PollEvent(&event) != 0)
            for (const auto &updatable : m_events_updatables_)
                updatable->Update(event);

        for (const auto &updatable : m_updatables_)
            updatable->Update(delta);

        if (event.type == SDL_QUIT)
            break;
    }
}

void GameLoop::AddUpdatable(IUpdatable &updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), &updatable) != m_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.push_back(&updatable);
}

void GameLoop::AddUpdatable(std::unique_ptr<IUpdatable> &&updatable)
{
    if (std::find(m_owned_updatables_.begin(), m_owned_updatables_.end(), updatable) != m_owned_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.push_back(updatable.get());
    m_owned_updatables_.push_back(std::move(updatable));
}

void GameLoop::RemoveUpdatable(const IUpdatable &updatable)
{
    auto find_iterator = std::find(m_updatables_.begin(), m_updatables_.end(), &updatable);

    if (find_iterator != m_updatables_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_updatables_.erase(find_iterator);
}

void GameLoop::AddEventsUpdatable(IEventsUpdatable &updatable)
{
    if (std::find(m_events_updatables_.begin(), m_events_updatables_.end(), &updatable) != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable already in loop");

    m_events_updatables_.push_back(&updatable);
}

void GameLoop::AddEventsUpdatable(std::unique_ptr<IEventsUpdatable> &&updatable)
{
    if (std::find(m_owned_events_updatables_.begin(), m_owned_events_updatables_.end(), updatable) != m_owned_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable already in loop");

    m_events_updatables_.push_back(updatable.get());
    m_owned_events_updatables_.push_back(std::move(updatable));
}

void GameLoop::RemoveEventsUpdatable(const IEventsUpdatable &updatable)
{
    auto find_iterator = std::find(m_events_updatables_.begin(), m_events_updatables_.end(), &updatable);

    if (find_iterator != m_events_updatables_.end())
        throw std::invalid_argument("EventsUpdatable doesn't in loop");

    m_events_updatables_.erase(find_iterator);
}
