#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_COMPONENTS_COLLISION_DETECTOR_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_COMPONENTS_COLLISION_DETECTOR_HPP_

#include <list>
#include <vector>
#include "shared_pointer.hpp"
#include "../physics_object.h"
#include "../collision_data.hpp"

namespace arkanoid
{
class CollisionDetector
{
public:
    std::list<CollisionData> Detect(std::vector<SharedPointer<IPhysicsObject>> &objects);
};
}

#endif
