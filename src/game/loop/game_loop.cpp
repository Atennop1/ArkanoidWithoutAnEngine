#include "game/loop/game_loop.hpp"
#include <stdexcept>
#include <algorithm>

namespace arkanoid
{
GameLoop::GameLoop(SharedPointer<IReadOnlyGameTime> &game_time, SharedPointer<ApplicationEvents> &events)
    : game_time_(game_time), events_(events) { }

void GameLoop::Activate()
{
    while (is_active_)
    {
        if (!game_time_->IsActive())
            continue;

        float delta = game_time_->Delta();
        for (auto &updatable: objects_)
            updatable->Update(delta);

        if (!events_->GetEventsOfType(SDL_QUIT).empty())
          is_active_ = false;
    }
}

void GameLoop::Add(SharedPointer<IGameLoopObject> &object)
{
    if (std::ranges::find(objects_.begin(), objects_.end(), object) != objects_.end())
        throw std::invalid_argument("Updatable already in loop");

    objects_.push_back(object);
}

void GameLoop::Remove(const IGameLoopObject &object)
{
    auto find_iterator = std::ranges::find_if(objects_.begin(), objects_.end(), [&](auto &pointer) { return pointer.Get() == &object; });

    if (find_iterator == objects_.end())
        throw std::invalid_argument("Updatable does not in loop");

    objects_.erase(find_iterator);
}
}
