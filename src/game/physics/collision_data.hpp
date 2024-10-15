#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_COLLISION_DATA_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_COLLISION_DATA_HPP_

#include "shared_pointer.hpp"

namespace arkanoid
{
class IPhysicsObject;

struct CollisionData
{
    SharedPointer<IPhysicsObject> collider;
    SharedPointer<IPhysicsObject> collidee;
};
}

#endif
