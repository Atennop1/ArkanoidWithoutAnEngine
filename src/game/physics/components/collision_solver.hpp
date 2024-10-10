#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_COMPONENTS_COLLISION_SOLVER_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_COMPONENTS_COLLISION_SOLVER_HPP_

#include <list>
#include "../collision_data.hpp"

namespace arkanoid
{
class CollisionSolver
{
public:
    void Solve(std::list<CollisionData> &collisions);
};
}

#endif
