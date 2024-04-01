#include "game_physics_loop.hpp"

GamePhysicsLoop::GamePhysicsLoop(std::shared_ptr<Box2D::World> &world)
        : m_world_(world) { }

void GamePhysicsLoop::Activate()
{
    m_is_active_ = true;
    Box2D::int32 velocityIterations = 6;
    Box2D::int32 positionIterations = 2;

    while (m_is_active_)
        m_world_->Step(m_time_step_, velocityIterations, positionIterations);
}

void GamePhysicsLoop::Deactivate()
{
    m_is_active_ = false;
}

void GamePhysicsLoop::AddPhysicsObject(IPhysicsObject &physics_object)
{
    if (std::find(m_physics_objects_.begin(), m_physics_objects_.end(), &physics_object) != m_physics_objects_.end())
        throw std::invalid_argument("PhysicsObject already in loop");

    m_physics_objects_.push_back(&physics_object);
}

void GamePhysicsLoop::RemovePhysicsObject(const IPhysicsObject &physics_object)
{
    auto find_iterator = std::find(m_physics_objects_.begin(), m_physics_objects_.end(), &physics_object);

    if (find_iterator != m_physics_objects_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    m_physics_objects_.erase(find_iterator);
}
