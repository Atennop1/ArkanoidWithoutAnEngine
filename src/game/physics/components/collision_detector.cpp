#include "collision_detector.hpp"

namespace arkanoid
{
    std::list<CollisionData> CollisionDetector::Detect(std::vector<SharedPointer<IPhysicsObject>> &objects)
    {
        std::list<CollisionData> collisions { };

        for (int i = 0; i < objects.size(); ++i)
            for (int j = i + 1; j < objects.size(); ++j)
                if (objects[i]->Right() >= objects[j]->Left() && objects[i]->Left() <= objects[j]->Right() && objects[i]->Bottom() >= objects[j]->Top() && objects[i]->Top() <= objects[j]->Bottom())
                    collisions.emplace_back(objects[i], objects[j]);

        return collisions;
    }
}