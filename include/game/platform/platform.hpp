#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PLATFORM_PLATFORM_HPP_

#include "platform_view.hpp"
#include "tools/shared_pointer.hpp"
#include "game/loop/objects/game_object.hpp"

namespace arkanoid
{
class Platform : public IGameObject
{
public:
    Platform(PhysicalProperties properties, SharedPointer<PlatformView> &platform_view);

    void Update(float delta) override;
    void Move(Vector2 move_vector);

private:
    SharedPointer<PlatformView> platform_view_;
};
}

#endif
