#ifndef ARKANOIDWITHOUTANENGINE_B305C8DB68BB4964A93BEEE562797695
#define ARKANOIDWITHOUTANENGINE_B305C8DB68BB4964A93BEEE562797695

#include "physics_object.h"
#include "Box2D.hpp"
#include "../game_loop.hpp"
#include "../time/read_only_game_time.hpp"
#include <vector>
#include <memory>

class GamePhysicsLoop : public IGameLoop
{
private:
    const float m_fps_ = 60.0f;
    const float m_time_step_ = 1.0f / m_fps_;

    const Box2D::Int32 m_velocity_iterations_ = 6;
    const Box2D::Int32 m_position_iterations_ = 2;

    IReadOnlyGameTime &m_game_time_;
    Box2D::World &m_world_;
    std::vector<IPhysicsObject*> m_physics_objects_ = { };

public:
    explicit GamePhysicsLoop(Box2D::World &world, IReadOnlyGameTime &game_time);
    ~GamePhysicsLoop() override = default;

    void Update() override;
    bool IsActive() override { return true; }

    void AddPhysicsObject(IPhysicsObject &physics_object);
    void RemovePhysicsObject(const IPhysicsObject &physics_object);
};

#endif
