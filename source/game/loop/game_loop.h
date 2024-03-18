#ifndef ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814
#define ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814

#include "updatables/updatable.h"
#include "updatables/events_updatable.h"
#include "time/game_time.h"
#include <list>

class GameLoop
{
private:
    std::list<IUpdatable*> m_updatables_;
    std::list<IEventsUpdatable*> m_events_updatables_;
    IReadOnlyGameTime &m_game_time_;

public:
    explicit GameLoop(IReadOnlyGameTime &game_time, const std::list<IUpdatable*> &updatables = std::list<IUpdatable*>(), const std::list<IEventsUpdatable*> &events_updatables = std::list<IEventsUpdatable*>());
    ~GameLoop();

    void AddUpdatable(IUpdatable *updatable);
    void RemoveUpdatable(const IUpdatable *updatable);

    void AddEventsUpdatable(IEventsUpdatable *updatable);
    void RemoveEventsUpdatable(const IEventsUpdatable *updatable);

    void Activate() const;
};

#endif
