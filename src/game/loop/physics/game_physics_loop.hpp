#ifndef ARKANOIDWITHOUTANENGINE_86223E08398A4495A18GE54TE4TTFEGE
#define ARKANOIDWITHOUTANENGINE_86223E08398A4495A18GE54TE4TTFEGE

#include "physics_object.h"
#include "Box2D/Box2D.hpp"
#include "../game_loop.hpp"
#include "../time/read_only_game_time.hpp"
#include <vector>
#include <memory>

class GamePhysicsLoop : public IGameLoop
{
private:
    const float m_fps_ = 60.0f;
    const float m_time_step_ = 1.0f / m_fps_;

    const Box2D::int32 m_velocity_iterations_ = 6;
    const Box2D::int32 m_position_iterations_ = 2;

    const std::shared_ptr<IReadOnlyGameTime> m_game_time_;
    std::vector<IPhysicsObject*> m_physics_objects_ = { };
    const std::shared_ptr<Box2D::World> m_world_;

public:
    explicit GamePhysicsLoop(std::shared_ptr<Box2D::World> &world, const std::shared_ptr<IReadOnlyGameTime> &game_time);
    ~GamePhysicsLoop() override = default;

    void Update() override;
    bool IsActive() override { return true; }

    void AddPhysicsObject(IPhysicsObject &physics_object);
    void RemovePhysicsObject(const IPhysicsObject &physics_object);
};

#endif
