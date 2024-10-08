#include "physics_simulation.hpp"
#include <algorithm>

arkanoid::PhysicsSimulation::PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> &objects)
    : objects_(objects) { }

arkanoid::PhysicsSimulation::PhysicsSimulation(std::vector<SharedPointer<IPhysicsObject>> &&objects)
    : objects_(objects) { }

void arkanoid::PhysicsSimulation::Update(float delta)
{
    elapsed_time_ += delta;

    while (last_update_time_ < elapsed_time_)
    {
        // collision detection logic...
        last_update_time_ += time_step_;
    }
}

void arkanoid::PhysicsSimulation::AddObject(SharedPointer<IPhysicsObject> &object)
{
    if (std::ranges::find(objects_.begin(), objects_.end(), object) != objects_.end())
        throw std::invalid_argument("PhysicsObject already in loop");

    objects_.push_back(object);
}

void arkanoid::PhysicsSimulation::RemoveObject(const IPhysicsObject &object)
{
    auto find_iterator = std::ranges::find_if(objects_.begin(), objects_.end(), [&](auto pointer) { return pointer.Get() == &object; });

    if (find_iterator == objects_.end())
        throw std::invalid_argument("PhysicsObject doesn't in loop");

    objects_.erase(find_iterator);
}