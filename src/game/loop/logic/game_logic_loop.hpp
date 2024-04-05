#ifndef ARKANOIDWITHOUTANENGINE_86223E08398A4495A18F95EECF1FA30C
#define ARKANOIDWITHOUTANENGINE_86223E08398A4495A18F95EECF1FA30C

#include "updatables/updatable.hpp"
#include "updatables/events_updatable.hpp"
#include "../time/game_time.hpp"
#include "../game_loop.hpp"
#include <vector>
#include <memory>

class GameLogicLoop : public IGameLoop
{
private:
    IReadOnlyGameTime &m_game_time_;
    bool m_is_active_ = true;

    std::vector<IUpdatable*> m_updatables_ = { };
    std::vector<IEventsUpdatable*> m_events_updatables_ = { };

public:
    explicit GameLogicLoop(IReadOnlyGameTime &game_time);
    ~GameLogicLoop() override = default;
    void Update() override;
    bool IsActive() override { return m_is_active_; }

    void AddUpdatable(IUpdatable &updatable);
    void RemoveUpdatable(const IUpdatable &updatable);

    void AddEventsUpdatable(IEventsUpdatable &updatable);
    void RemoveEventsUpdatable(const IEventsUpdatable &updatable);
};

#endif
