#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_HPP_

#include "wall_view.hpp"
#include "tools/shared_pointer.hpp"
#include "engine/loop/objects/game_object.hpp"

namespace arkanoid
{
class Wall : public IGameObject
{
public:
    Wall(PhysicalProperties physical_properties, SharedPointer<WallView> wall_view);

    virtual void Update(float delta) override;

private:
    SharedPointer<WallView> wall_view_;
};
}

#endif
