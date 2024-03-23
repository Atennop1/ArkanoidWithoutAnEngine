#ifndef ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814
#define ARKANOIDWITHOUTANENGINE_20D6708542884BF79266FBB1F0529814

#include "updatables/updatable.h"
#include "updatables/events_updatable.h"
#include "time/game_time.h"
#include <vector>
#include <memory>

class GameLoop
{
private:
    const std::shared_ptr<IReadOnlyGameTime> &m_game_time_;
    std::vector<IUpdatable*> m_updatables_;
    std::vector<std::unique_ptr<IUpdatable>> m_unique_updatables_;

    std::vector<IEventsUpdatable*> m_events_updatables_;
    std::vector<std::unique_ptr<IEventsUpdatable>> m_unique_events_updatables_;

public:
    explicit GameLoop(const std::shared_ptr<IReadOnlyGameTime> &game_time);

    void AddUpdatable(IUpdatable &updatable);
    void AddUpdatable(std::unique_ptr<IUpdatable> &&updatable);
    void RemoveUpdatable(const IUpdatable &updatable);
    void RemoveUpdatable(const std::unique_ptr<IUpdatable> &&updatable);

    void AddEventsUpdatable(IEventsUpdatable &updatable);
    void AddEventsUpdatable(std::unique_ptr<IEventsUpdatable> &&updatable);
    void RemoveEventsUpdatable(const IEventsUpdatable &updatable);
    void RemoveEventsUpdatable(const std::unique_ptr<IEventsUpdatable> &&updatable);

    void Activate() const;
};

#endif
