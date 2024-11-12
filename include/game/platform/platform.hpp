#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_HPP_

#include "platform_view.hpp"
#include <genesis/loop/objects/game_object.hpp>
#include <genesis/memory/shared_pointer.hpp>

namespace arkanoid
{
class Platform : public genesis::IGameObject
{
public:
    Platform(genesis::PhysicalProperties properties, const genesis::SharedPointer<PlatformView> &platform_view);
    void Move(genesis::Vector2 move_vector);

    virtual void Update(float delta) override;
    virtual void HandleCollisionStart(genesis::IPhysicsObject *other) override;

private:
    genesis::SharedPointer<PlatformView> platform_view_;
};
}

#endif
