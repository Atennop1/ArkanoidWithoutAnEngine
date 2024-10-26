#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_PHYSICS_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_PHYSICS_OBJECT_HPP_

#include "physical_properties.hpp"

namespace arkanoid
{
class IPhysicsObject
{
public:
    virtual ~IPhysicsObject() = default;

    virtual void Destroy() { is_destroyed_ = true; }
    virtual void HandleCollisionStart(IPhysicsObject* other) = 0;
    virtual void FixedUpdate(float fixed_delta) = 0;

    virtual bool IsDestroyed() { return is_destroyed_; }
    virtual PhysicalProperties& Properties() = 0;

private:
    bool is_destroyed_ = false;
};
}

#endif
