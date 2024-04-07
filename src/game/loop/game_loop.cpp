#include <stdexcept>
#include "game_loop.hpp"
#include "SDL.h"

GameLoop::GameLoop(SharedPointer<IReadOnlyGameTime> &game_time)
    : m_game_time_(game_time) { }

void GameLoop::Activate()
{
    while (m_is_active_)
    {
        if (!m_game_time_->IsActive())
            continue;

        SDL_Event event;
        float delta = m_game_time_->Delta();

        while (SDL_PollEvent(&event) != 0)
        {
            for (const auto &updatable: m_events_objects_)
                updatable->Update(event);

            if (event.type == SDL_QUIT)
                m_is_active_ = false;
        }

        for (const auto &updatable: m_objects_)
            updatable->Update(delta);
    }
}

void GameLoop::AddObject(IGameLoopObject &object)
{
    if (std::find(m_objects_.begin(), m_objects_.end(), &object) != m_objects_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_objects_.push_back(&object);
}

void GameLoop::AddObject(SharedPointer<IGameLoopObject> &object)
{
    AddObject(*object.Get());
    m_shared_objects_.push_back(object);
}

void GameLoop::RemoveObject(const IGameLoopObject &object)
{
    auto find_iterator = std::find(m_objects_.begin(), m_objects_.end(), &object);
    if (find_iterator == m_objects_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_objects_.erase(find_iterator);
    auto shared_find_iterator = std::find_if(m_shared_objects_.begin(), m_shared_objects_.end(), [&](SharedPointer<IGameLoopObject> &pointer) { return pointer.Get() == &object; });

    if (shared_find_iterator != m_shared_objects_.end())
        m_shared_objects_.erase(shared_find_iterator);
}

void GameLoop::AddEventsObject(IGameLoopEventsObject &object)
{
    if (std::find(m_events_objects_.begin(), m_events_objects_.end(), &object) != m_events_objects_.end())
        throw std::invalid_argument("EventsUpdatable already in loop");

    m_events_objects_.push_back(&object);
}

void GameLoop::AddEventsObject(SharedPointer<IGameLoopEventsObject> &object)
{
    AddEventsObject(*object.Get());
    m_shared_events_objects_.push_back(object);
}

void GameLoop::RemoveEventsObject(const IGameLoopEventsObject &object)
{
    auto find_iterator = std::find(m_events_objects_.begin(), m_events_objects_.end(), &object);
    if (find_iterator == m_events_objects_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_events_objects_.erase(find_iterator);
    auto shared_find_iterator = std::find_if(m_shared_events_objects_.begin(), m_shared_events_objects_.end(), [&](SharedPointer<IGameLoopEventsObject> &pointer) { return pointer.Get() == &object; });

    if (shared_find_iterator != m_shared_events_objects_.end())
        m_shared_events_objects_.erase(shared_find_iterator);
}