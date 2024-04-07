#ifndef ARKANOIDWITHOUTANENGINE_18E73548EBC042429AF06C1A32E76175
#define ARKANOIDWITHOUTANENGINE_18E73548EBC042429AF06C1A32E76175

#include "updatables/game_loop_object.hpp"
#include "updatables/game_loop_events_object.hpp"
#include "time/game_time.hpp"
#include "shared_pointer.hpp"
#include <vector>
#include <memory>

class GameLoop
{
private:
    SharedPointer<IReadOnlyGameTime> m_game_time_;
    bool m_is_active_ = true;

    std::vector<IGameLoopObject*> m_objects_ = { };
    std::vector<SharedPointer<IGameLoopObject>> m_shared_objects_ = { };

    std::vector<IGameLoopEventsObject*> m_events_objects_ = { };
    std::vector<SharedPointer<IGameLoopEventsObject>> m_shared_events_objects_ = { };

public:
    explicit GameLoop(SharedPointer<IReadOnlyGameTime> &game_time);
    void Activate();

    void AddObject(IGameLoopObject &object);
    void AddObject(SharedPointer<IGameLoopObject> &object);
    void AddObject(SharedPointer<IGameLoopObject> &&object) { AddObject(object); }
    void RemoveObject(const IGameLoopObject &object);

    void AddEventsObject(IGameLoopEventsObject &object);
    void AddEventsObject(SharedPointer<IGameLoopEventsObject> &object);
    void AddEventsObject(SharedPointer<IGameLoopEventsObject> &&object) { AddEventsObject(object); }
    void RemoveEventsObject(const IGameLoopEventsObject &object);
};

#endif
