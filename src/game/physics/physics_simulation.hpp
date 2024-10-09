#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_SIMULATION_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_SIMULATION_HPP_

#include "physics_object.h"
#include "../loop/time/read_only_game_time.hpp"
#include "../loop/objects/game_loop_object.hpp"
#include "shared_pointer.hpp"
#include <vector>

namespace arkanoid
{
    class PhysicsSimulation : public IGameLoopObject
    {
    private:
        float elapsed_time_ = 0.0f;
        float last_update_time_ = 0.0f;

        const float time_step_ = 1.0f / 60.0f;
        std::vector<SharedPointer<IPhysicsObject>> objects_ = { };

    public:
        PhysicsSimulation() : PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> { }) { }
        explicit PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> &objects);
        explicit PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> &&objects);

        void Update(float delta) override;
        void AddObject(SharedPointer<IPhysicsObject> &object);
        void RemoveObject(const IPhysicsObject &object);

        void AddObject(IPhysicsObject &object) { AddObject(SharedPointer(&object)); }
        void AddObject(SharedPointer<IPhysicsObject> &&object) { AddObject(object); }
    };
}

#endif
