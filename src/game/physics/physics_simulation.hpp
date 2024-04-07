#ifndef ARKANOIDWITHOUTANENGINE_6AC28A8B93A9403F88348E9AA6CEE1DF
#define ARKANOIDWITHOUTANENGINE_6AC28A8B93A9403F88348E9AA6CEE1DF

#include "physics_object.h"
#include "Box2D.hpp"
#include "../loop/time/read_only_game_time.hpp"
#include "shared_pointer.hpp"
#include "../loop/updatables/game_loop_object.hpp"
#include <vector>
#include <iostream>

class PhysicsSimulation : public IGameLoopObject
{
private:
    const float m_time_step_ = 1.0f / 60.0f;
    const Box2D::Int32 m_velocity_iterations_ = 6;
    const Box2D::Int32 m_position_iterations_ = 2;

    float m_elapsed_time_ = 0.0f;
    float m_last_update_time_ = 0.0f;
    SharedPointer<Box2D::World> m_world_;

    std::vector<IPhysicsObject*> m_physics_objects_ = { };
    std::vector<SharedPointer<IPhysicsObject>> m_shared_physics_objects_ = { };

public:
    explicit PhysicsSimulation(SharedPointer<Box2D::World> &world);
    void Update(float delta) override;

    // later there will be adding of ICollider classes to Box2D::World
    void AddPhysicsObject(IPhysicsObject &physics_object);
    void AddPhysicsObject(SharedPointer<IPhysicsObject> &physics_object);
    void AddPhysicsObject(SharedPointer<IPhysicsObject> &&physics_object) { AddPhysicsObject(physics_object); }
    void RemovePhysicsObject(const IPhysicsObject &physics_object);
};

#endif
