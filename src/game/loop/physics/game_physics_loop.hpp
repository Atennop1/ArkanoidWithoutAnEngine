#ifndef ARKANOIDWITHOUTANENGINE_86223E08398A4495A18F95EECF1FA30C
#define ARKANOIDWITHOUTANENGINE_86223E08398A4495A18F95EECF1FA30C

#include "physics_object.h"
#include "Box2D/Box2D.hpp"
#include <vector>
#include <memory>

class GamePhysicsLoop
{
private:
    const float m_fps_ = 60.0f;
    const float m_time_step_ = 1.0f / m_fps_;

    bool m_is_active_ = false;
    const std::shared_ptr<Box2D::World> m_world_;
    std::vector<IPhysicsObject*> m_physics_objects_ = { };

public:
    explicit GamePhysicsLoop(std::shared_ptr<Box2D::World> &world);
    void Activate();
    void Deactivate();

    void AddPhysicsObject(IPhysicsObject &physics_object);
    void RemovePhysicsObject(const IPhysicsObject &physics_object);
};

#endif
