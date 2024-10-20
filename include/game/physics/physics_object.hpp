#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_PHYSICS_OBJECT_H_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_PHYSICS_OBJECT_H_

#include "physical_properties.hpp"

namespace arkanoid
{
class IPhysicsObject
{
public:
    virtual ~IPhysicsObject() = default;

    virtual void FixedUpdate(float fixed_delta) = 0;
    virtual void HandleCollisionStart(IPhysicsObject* other) = 0;
    virtual PhysicalProperties& Properties() = 0;
};
}

#endif
