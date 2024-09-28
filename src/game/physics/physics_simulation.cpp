#include "physics_simulation.hpp"
#include <algorithm>

arkanoid::PhysicsSimulation::PhysicsSimulation(SharedPointer<box2d::World> &world)
    : m_world_(world) { }

void arkanoid::PhysicsSimulation::Update(float delta)
{
    m_elapsed_time_ += delta;

    while (m_last_update_time_ < m_elapsed_time_)
    {
        m_world_->Step(m_time_step_, m_velocity_iterations_, m_position_iterations_);
        m_last_update_time_ += m_time_step_;
    }
}

void arkanoid::PhysicsSimulation::AddObject(SharedPointer<IPhysicsObject> &object)
{
    if (std::ranges::find(m_objects_.begin(), m_objects_.end(), object) != m_objects_.end())
        throw std::invalid_argument("PhysicsObject already in loop");

    m_objects_.push_back(object);
}

void arkanoid::PhysicsSimulation::RemoveObject(const IPhysicsObject &object)
{
    auto find_iterator = std::ranges::find_if(m_objects_.begin(), m_objects_.end(), [&](auto pointer) { return pointer.Get() == &object; });

    if (find_iterator == m_objects_.end())
        throw std::invalid_argument("PhysicsObject doesn't in loop");

    m_objects_.erase(find_iterator);
}