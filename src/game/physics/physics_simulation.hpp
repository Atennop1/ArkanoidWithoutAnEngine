#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_SIMULATION_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_SIMULATION_HPP_

#include "physics_object.h"
#include "../loop/time/read_only_game_time.hpp"
#include "../loop/objects/game_loop_object.hpp"
#include "shared_pointer.hpp"
#include "components/collision_detector.hpp"
#include "components/collision_solver.hpp"
#include <vector>

namespace arkanoid
{
class PhysicsSimulation : public IGameLoopObject
{
private:
    float elapsed_time_ = 0.0f;
    float last_update_time_ = 0.0f;
    const float time_step_ = 1.0f / 60.0f;

    SharedPointer<CollisionDetector> collision_detector_;
    SharedPointer<CollisionSolver> collision_solver_;
    std::vector<SharedPointer<IPhysicsObject>> objects_ = {};

public:
    PhysicsSimulation(SharedPointer<CollisionDetector> collision_detector, SharedPointer<CollisionSolver> collision_solver, std::vector<SharedPointer<IPhysicsObject>> &objects);
    PhysicsSimulation(SharedPointer<CollisionDetector> collision_detector, SharedPointer<CollisionSolver> collision_solver) : PhysicsSimulation(collision_detector, collision_solver, { }) { }
    PhysicsSimulation(SharedPointer<CollisionDetector> collision_detector, SharedPointer<CollisionSolver> collision_solver, std::vector<SharedPointer<IPhysicsObject>> &&objects) : PhysicsSimulation(collision_detector, collision_solver, objects) { }

    void Update(float delta) override;
    void Add(SharedPointer<IPhysicsObject> &object);
    void Remove(const IPhysicsObject &object);

    void Add(IPhysicsObject &object) { Add(SharedPointer(&object)); }
    void Add(SharedPointer<IPhysicsObject> &&object) { Add(object); }
};
}

#endif
