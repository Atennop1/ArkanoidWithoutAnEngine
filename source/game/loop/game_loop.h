#ifndef ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814
#define ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814

#include "updatables/updatable.h"
#include "updatables/events_updatable.h"
#include "time/game_time.h"
#include <vector>

class GameLoop
{
private:
    IReadOnlyGameTime &m_game_time_;
    std::vector<std::reference_wrapper<IUpdatable>> m_updatables_;
    std::vector<std::reference_wrapper<IEventsUpdatable>> m_events_updatables_;

public:
    explicit GameLoop(IReadOnlyGameTime &game_time);
    GameLoop(IReadOnlyGameTime &game_time, const std::vector<std::reference_wrapper<IUpdatable>> &updatables);
    GameLoop(IReadOnlyGameTime &game_time, const std::vector<std::reference_wrapper<IUpdatable>> &updatables, const std::vector<std::reference_wrapper<IEventsUpdatable>> &events_updatables);

    void AddUpdatable(IUpdatable &updatable);
    void RemoveUpdatable(const IUpdatable &updatable);

    void AddEventsUpdatable(IEventsUpdatable &updatable);
    void RemoveEventsUpdatable(const IEventsUpdatable &updatable);

    void Activate() const;
};

#endif
