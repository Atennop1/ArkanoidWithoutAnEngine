#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_SIMULATION_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_SIMULATION_HPP_

#include "physics_object.h"
#include "../loop/time/read_only_game_time.hpp"
#include "../loop/game_loop_object.hpp"
#include <vector>
#include "Box2D.hpp"
#include "shared_pointer.hpp"

namespace arkanoid
{
    class PhysicsSimulation : public IGameLoopObject
    {
    private:
        const float time_step_ = 1.0f / 60.0f;
        const box2d::Int32 velocity_iterations_ = 6;
        const box2d::Int32 position_iterations_ = 2;

        float elapsed_time_ = 0.0f;
        float last_update_time_ = 0.0f;

        SharedPointer<box2d::World> world_;
        std::vector<SharedPointer<IPhysicsObject>> objects_ = {};

    public:
        explicit PhysicsSimulation(SharedPointer<box2d::World> &world);
        void Update(float delta) override;

        // later there will be adding of ICollider classes to Box2D::World
        void AddObject(SharedPointer<IPhysicsObject> &object);
        void RemoveObject(const IPhysicsObject &object);

        void AddObject(IPhysicsObject &object) { AddObject(SharedPointer(&object)); }
        void AddObject(SharedPointer<IPhysicsObject> &&object) { AddObject(object); }
    };
}

#endif
