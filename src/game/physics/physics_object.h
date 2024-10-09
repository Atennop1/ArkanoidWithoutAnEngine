#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_OBJECT_H_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_OBJECT_H_

#include "../math/vector2.hpp"

namespace arkanoid
{
class IPhysicsObject
{
public:
    virtual ~IPhysicsObject() = default;

    virtual Vector2 GetPosition() = 0;
    virtual void SetPosition(Vector2 position) = 0;

    virtual void FixedUpdate(float fixed_delta) = 0;
    virtual void HandleCollisionStart() = 0;
};
}

#endif
