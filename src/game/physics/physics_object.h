#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_OBJECT_H_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_OBJECT_H_

#include "../math/vector2.hpp"
#include "collision_data.hpp"

namespace arkanoid
{
class IPhysicsObject
{
public:
    virtual ~IPhysicsObject() = default;

    virtual void FixedUpdate(float fixed_delta) = 0;
    virtual void HandleCollisionStart(CollisionData data) = 0;


    virtual Vector2 Position() = 0;
    virtual void SetPosition(Vector2 position) = 0;

    virtual Vector2 Size() = 0;
    virtual void SetSize(Vector2 size) = 0;

    virtual Vector2 Velocity() = 0;
    virtual void SetVelocity(Vector2 velocity) = 0;

    virtual Vector2 Acceleration() = 0;
    virtual void SetAcceleration(Vector2 acceleration) = 0;


    float Left() { return Position().X() - Size().X() / 2.f; }
    float Right() { return Position().X() + Size().X() / 2.f; }
    float Top() { return Position().Y() - Size().Y() / 2.f; }
    float Bottom() { return Position().Y() + Size().Y() / 2.f; }
};
}

#endif
