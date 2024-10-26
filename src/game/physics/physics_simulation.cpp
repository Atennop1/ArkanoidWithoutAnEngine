#include "game/physics/physics_simulation.hpp"
#include <algorithm>
#include <list>

namespace arkanoid
{
void PhysicsSimulation::Update(float delta)
{
    elapsed_time_ += delta;

    while (last_update_time_ < elapsed_time_)
    {
        for (auto &physics_object: objects_)
            if (physics_object->IsDestroyed())
                std::remove(objects_.begin(), objects_.end(), physics_object), objects_.end();

        std::list<std::pair<IPhysicsObject*, IPhysicsObject*>> collisions { };
        for (auto physics_object : objects_)
        {
            physics_object->Properties().velocity = physics_object->Properties().velocity + physics_object->Properties().acceleration * time_step_;
            physics_object->Properties().position = physics_object->Properties().position + physics_object->Properties().velocity * time_step_;
        }

        for (auto object : objects_)
        {
            for (auto object2 : objects_)
            {
                if (auto find_iterator = std::find_if(collisions.begin(), collisions.end(), [&](auto pair) { return pair.first == object.Get(); }); find_iterator != collisions.end() || object == object2)
                    continue;

                if (object->Properties().Right() >= object2->Properties().Left()
                    && object->Properties().Left() <= object2->Properties().Right()
                    && object->Properties().Bottom() >= object2->Properties().Top()
                    && object->Properties().Top() <= object2->Properties().Bottom()) collisions.emplace_back(object.Get(), object2.Get());
        }}

        for (auto collision : collisions)
            collision.first->HandleCollisionStart(collision.second);

        last_update_time_ += time_step_;
    }
}

void PhysicsSimulation::Add(SharedPointer<IPhysicsObject> &object)
{
    if (std::ranges::find(objects_.begin(), objects_.end(), object) != objects_.end())
        throw std::invalid_argument("PhysicsObject already in loop");

    objects_.push_back(object);
}

void PhysicsSimulation::Remove(const IPhysicsObject &object)
{
    auto find_iterator = std::ranges::find_if(objects_.begin(), objects_.end(), [&](auto pointer) { return pointer.Get() == &object; });

    if (find_iterator == objects_.end())
        throw std::invalid_argument("PhysicsObject doesn't in loop");

    objects_.erase(find_iterator);
}
}
