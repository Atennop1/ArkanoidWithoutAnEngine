#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_WALL_WALL_HPP_

#include "wall_view.hpp"
#include <genesis/physics/physical_properties.hpp>
#include <genesis/memory/shared_pointer.hpp>
#include <genesis/loop/objects/game_object.hpp>

namespace arkanoid
{
class Wall : public genesis::IGameObject
{
public:
    Wall(genesis::PhysicalProperties physical_properties, const genesis::SharedPointer<WallView> &wall_view);

    virtual void Update(float delta) override;

private:
    genesis::SharedPointer<WallView> wall_view_;
};
}

#endif
