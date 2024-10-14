#include "physics_simulation.hpp"
#include <algorithm>

namespace arkanoid
{
PhysicsSimulation::PhysicsSimulation(SharedPointer<CollisionDetector> collision_detector, SharedPointer<CollisionSolver> collision_solver, std::vector<SharedPointer<IPhysicsObject>> &objects)
    : collision_solver_(collision_solver), collision_detector_(collision_detector), objects_(objects) { }

void PhysicsSimulation::Update(float delta)
{
    elapsed_time_ += delta;

    while (last_update_time_ < elapsed_time_)
    {
        for (auto physics_object : objects_)
        {
            physics_object->SetVelocity(physics_object->Velocity() + physics_object->Acceleration() * delta);
            physics_object->SetPosition(physics_object->Position() + physics_object->Velocity() * delta);
        }

        auto collisions = collision_detector_->Detect(objects_);
        collision_solver_->Solve(collisions);
        last_update_time_ += time_step_;
    }
}

void PhysicsSimulation::AddObject(SharedPointer<IPhysicsObject> &object)
{
    if (std::ranges::find(objects_.begin(), objects_.end(), object) != objects_.end())
        throw std::invalid_argument("PhysicsObject already in loop");

    objects_.push_back(object);
}

void PhysicsSimulation::RemoveObject(const IPhysicsObject &object)
{
    auto find_iterator = std::ranges::find_if(objects_.begin(), objects_.end(), [&](auto pointer) { return pointer.Get() == &object; });

    if (find_iterator == objects_.end())
        throw std::invalid_argument("PhysicsObject doesn't in loop");

    objects_.erase(find_iterator);
}
}
