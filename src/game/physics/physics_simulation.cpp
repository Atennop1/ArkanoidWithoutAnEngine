#include "physics_simulation.hpp"
#include <algorithm>

PhysicsSimulation::PhysicsSimulation(SharedPointer<Box2D::World> &world)
    : m_world_(world) { }

void PhysicsSimulation::Update(float delta)
{
    m_elapsed_time_ += delta;

    while (m_last_update_time_ < m_elapsed_time_)
    {
        m_world_->Step(m_time_step_, m_velocity_iterations_, m_position_iterations_);
        m_last_update_time_ += m_time_step_;
    }
}

void PhysicsSimulation::AddPhysicsObject(IPhysicsObject &physics_object)
{
    if (std::ranges::find(m_physics_objects_.begin(), m_physics_objects_.end(), &physics_object) != m_physics_objects_.end())
        throw std::invalid_argument("PhysicsObject already in loop");

    m_physics_objects_.push_back(&physics_object);
}

void PhysicsSimulation::AddPhysicsObject(SharedPointer<IPhysicsObject> &physics_object)
{
    AddPhysicsObject(*physics_object.Get());
    m_shared_physics_objects_.push_back(physics_object);
}

void PhysicsSimulation::RemovePhysicsObject(const IPhysicsObject &physics_object)
{
    auto find_iterator = std::ranges::find(m_physics_objects_.begin(), m_physics_objects_.end(), &physics_object);

    if (find_iterator != m_physics_objects_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_physics_objects_.erase(find_iterator);
    auto shared_find_iterator = std::ranges::find_if(m_shared_physics_objects_.begin(), m_shared_physics_objects_.end(), [&](SharedPointer<IPhysicsObject> &pointer) { return pointer.Get() == &physics_object; });

    if (shared_find_iterator != m_shared_physics_objects_.end())
        m_shared_physics_objects_.erase(shared_find_iterator);
}