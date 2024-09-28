#ifndef ARKANOIDWITHOUTANENGINE_6AC28A8B93A9403F88348E9AA6CEE1DF
#define ARKANOIDWITHOUTANENGINE_6AC28A8B93A9403F88348E9AA6CEE1DF

#include "physics_object.h"
#include "../loop/time/read_only_game_time.hpp"
#include "../loop/game_loop_object.hpp"
#include <vector>
#include "Box2D.hpp"
#include "shared_pointer.hpp"

class PhysicsSimulation : public IGameLoopObject
{
private:
    const float m_time_step_ = 1.0f / 60.0f;
    const box2d::Int32 m_velocity_iterations_ = 6;
    const box2d::Int32 m_position_iterations_ = 2;

    float m_elapsed_time_ = 0.0f;
    float m_last_update_time_ = 0.0f;

    SharedPointer<box2d::World> m_world_;
    std::vector<SharedPointer<IPhysicsObject>> m_objects_ = { };

public:
    explicit PhysicsSimulation(SharedPointer<box2d::World> &world);
    void Update(float delta) override;

    // later there will be adding of ICollider classes to Box2D::World
    void AddObject(SharedPointer<IPhysicsObject> &object);
    void RemoveObject(const IPhysicsObject &object);

    void AddObject(IPhysicsObject &object) { AddObject(SharedPointer(&object)); }
    void AddObject(SharedPointer<IPhysicsObject> &&object) { AddObject(object); }
};

#endif
