#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_GAME_LOOP_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_GAME_LOOP_HPP_

#include "objects/game_loop_object.hpp"
#include "time/game_time.hpp"
#include "shared_pointer.hpp"
#include "../events/application_events.hpp"
#include <vector>

namespace arkanoid
{
    class GameLoop
    {
    private:
        bool is_active_ = true;
        SharedPointer<IReadOnlyGameTime> game_time_;

        SharedPointer<ApplicationEvents> events_;
        std::vector<SharedPointer<IGameLoopObject>> objects_ = {};

    public:
        GameLoop(SharedPointer<IReadOnlyGameTime> &game_time, SharedPointer<ApplicationEvents> &events);
        void Activate();

        void Add(SharedPointer<IGameLoopObject> &object);
        void Remove(const IGameLoopObject &object);

        void Add(IGameLoopObject &object) { Add(SharedPointer<IGameLoopObject>(&object)); }
        void Add(SharedPointer<IGameLoopObject> &&object) { Add(object); }
    };
}

#endif
