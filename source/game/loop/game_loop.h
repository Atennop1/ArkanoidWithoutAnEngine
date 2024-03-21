#ifndef ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814
#define ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814

#include "updatables/updatable.h"
#include "updatables/events_updatable.h"
#include "time/game_time.h"
#include "time/average_game_time.h"
#include <vector>

class GameLoop
{
private:
    IReadOnlyGameTime &m_game_time_;
    std::vector<IUpdatable*> m_updatables_;
    std::vector<IEventsUpdatable*> m_events_updatables_;

public:
    explicit GameLoop(IReadOnlyGameTime &game_time);

    void AddUpdatable(IUpdatable &updatable);
    void RemoveUpdatable(const IUpdatable &updatable);

    void AddEventsUpdatable(IEventsUpdatable &updatable);
    void RemoveEventsUpdatable(const IEventsUpdatable &updatable);

    void Activate() const;
};

#endif
