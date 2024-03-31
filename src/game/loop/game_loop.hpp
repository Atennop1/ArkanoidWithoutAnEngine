#ifndef ARKANOIDWITHOUTANENGINE_F000DC1F8B764AB0ABFF0DD8D9AFB876
#define ARKANOIDWITHOUTANENGINE_F000DC1F8B764AB0ABFF0DD8D9AFB876

#include "updatables/updatable.hpp"
#include "updatables/events_updatable.hpp"
#include "time/game_time.hpp"
#include <vector>
#include <memory>

class GameLoop
{
private:
    const std::shared_ptr<IReadOnlyGameTime> &m_game_time_;

    std::vector<IUpdatable*> m_updatables_ = { };
    std::vector<std::unique_ptr<IUpdatable>> m_owned_updatables_ = { };

    std::vector<IEventsUpdatable*> m_events_updatables_ = { };
    std::vector<std::unique_ptr<IEventsUpdatable>> m_owned_events_updatables_ = { };

public:
    explicit GameLoop(const std::shared_ptr<IReadOnlyGameTime> &game_time);
    void Activate() const;

    void AddUpdatable(IUpdatable &updatable);
    void AddUpdatable(std::unique_ptr<IUpdatable> &&updatable);
    void RemoveUpdatable(const IUpdatable &updatable);

    void AddEventsUpdatable(IEventsUpdatable &updatable);
    void AddEventsUpdatable(std::unique_ptr<IEventsUpdatable> &&updatable);
    void RemoveEventsUpdatable(const IEventsUpdatable &updatable);
};

#endif
