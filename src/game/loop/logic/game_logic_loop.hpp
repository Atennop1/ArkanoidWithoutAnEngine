#ifndef ARKANOIDWITHOUTANENGINE_86223E08398A4495A18F95EECF1FA30C
#define ARKANOIDWITHOUTANENGINE_86223E08398A4495A18F95EECF1FA30C

#include "updatables/updatable.hpp"
#include "updatables/events_updatable.hpp"
#include "../time/game_time.hpp"
#include "../game_loop.hpp"
#include "shared_pointer.hpp"
#include <vector>
#include <memory>

class GameLogicLoop : public IGameLoop
{
private:
    SharedPointer<IReadOnlyGameTime> m_game_time_;
    bool m_is_active_ = true;

    std::vector<IUpdatable*> m_updatables_ = { };
    std::vector<SharedPointer<IUpdatable>> m_shared_updatables_ = { };

    std::vector<IEventsUpdatable*> m_events_updatables_ = { };
    std::vector<SharedPointer<IEventsUpdatable>> m_shared_events_updatables_ = { };

public:
    explicit GameLogicLoop(SharedPointer<IReadOnlyGameTime> &game_time);
    ~GameLogicLoop() override = default;
    void Update() override;
    bool IsActive() override { return m_is_active_; }

    void AddUpdatable(IUpdatable &updatable);
    void AddUpdatable(SharedPointer<IUpdatable> &updatable);
    void AddUpdatable(SharedPointer<IUpdatable> &&updatable) { AddUpdatable(updatable); }
    void RemoveUpdatable(const IUpdatable &updatable);

    void AddEventsUpdatable(IEventsUpdatable &updatable);
    void AddEventsUpdatable(SharedPointer<IEventsUpdatable> &updatable);
    void AddEventsUpdatable(SharedPointer<IEventsUpdatable> &&updatable) { AddEventsUpdatable(updatable); }
    void RemoveEventsUpdatable(const IEventsUpdatable &updatable);
};

#endif
