#include "game_physics_loop.hpp"

GamePhysicsLoop::GamePhysicsLoop(std::shared_ptr<Box2D::World> &world, const std::shared_ptr<IReadOnlyGameTime> &game_time)
    : m_world_(world), m_game_time_(game_time) { }

void GamePhysicsLoop::Update()
{
    if (m_game_time_->IsActive() && IsActive())
        m_world_->Step(m_time_step_, m_velocity_iterations_, m_position_iterations_);
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
