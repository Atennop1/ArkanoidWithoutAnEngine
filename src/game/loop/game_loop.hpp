#ifndef ARKANOIDWITHOUTANENGINE_18E73548EBC042429AF06C1A32E76175
#define ARKANOIDWITHOUTANENGINE_18E73548EBC042429AF06C1A32E76175

#include "game_loop_object.hpp"
#include "time/game_time.hpp"
#include "shared_pointer.hpp"
#include "../events/application_events.hpp"
#include <vector>

class GameLoop
{
private:
    bool m_is_active_ = true;
    SharedPointer<IReadOnlyGameTime> m_game_time_;

    SharedPointer<ApplicationEvents> m_events_;
    std::vector<SharedPointer<IGameLoopObject>> m_objects_ = { };

public:
    GameLoop(SharedPointer<IReadOnlyGameTime> &game_time, SharedPointer<ApplicationEvents> &events);

    void Activate();
    void Add(SharedPointer<IGameLoopObject> &object);
    void Remove(const IGameLoopObject &object);

    void Add(IGameLoopObject &object) { Add(SharedPointer<IGameLoopObject>(&object)); }
    void Add(SharedPointer<IGameLoopObject> &&object) { Add(object); }
};

#endif
