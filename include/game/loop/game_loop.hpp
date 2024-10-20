#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LOOP_GAME_LOOP_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LOOP_GAME_LOOP_HPP_

#include "objects/game_loop_object.hpp"
#include "time/game_time.hpp"
#include "game/events/application_events.hpp"
#include "tools/shared_pointer.hpp"
#include <vector>

namespace arkanoid
{
class GameLoop
{
public:
    GameLoop(SharedPointer<IReadOnlyGameTime> &game_time, SharedPointer<ApplicationEvents> &events);
    void Activate();

    void Add(SharedPointer<IGameLoopObject> &object);
    void Remove(const IGameLoopObject &object);

    void Add(IGameLoopObject &object) { Add(SharedPointer<IGameLoopObject>(&object)); }
    void Add(SharedPointer<IGameLoopObject> &&object) { Add(object); }

private:
    bool is_active_ = true;
    SharedPointer<IReadOnlyGameTime> game_time_;

    SharedPointer<ApplicationEvents> events_;
    std::vector<SharedPointer<IGameLoopObject>> objects_ = { };
};
}

#endif
