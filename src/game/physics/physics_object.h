#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_OBJECT_H_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_PHYSICS_OBJECT_H_

namespace arkanoid
{
    class IPhysicsObject
    {
    public:
        virtual ~IPhysicsObject() = default;

        virtual void FixedUpdate(float fixed_delta) = 0;
    };
}

#endif
