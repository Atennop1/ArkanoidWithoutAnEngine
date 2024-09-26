#include "game_loop.hpp"
#include <stdexcept>
#include <algorithm>

GameLoop::GameLoop(SharedPointer<IReadOnlyGameTime> &game_time, SharedPointer<ApplicationEvents> &events)
    : m_game_time_(game_time), m_events_(events) { }

void GameLoop::Activate()
{
    while (m_is_active_)
    {
        if (!m_game_time_->IsActive())
            continue;

        float delta = m_game_time_->Delta();
        for (auto &updatable: m_objects_)
            updatable->Update(delta);

        if (!m_events_->GetEventsOfType(SDL_QUIT).empty())
            m_is_active_ = false;
    }
}

void GameLoop::Add(SharedPointer<IGameLoopObject> &object)
{
    if (std::ranges::find(m_objects_.begin(), m_objects_.end(), object) != m_objects_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_objects_.push_back(object);
}

void GameLoop::Remove(const IGameLoopObject &object)
{
    auto find_iterator = std::ranges::find_if(m_objects_.begin(), m_objects_.end(), [&](auto &pointer) { return pointer.Get() == &object; });

    if (!(find_iterator != m_objects_.end()))
        throw std::invalid_argument("Updatable does not in loop");

    m_objects_.erase(find_iterator);
}