#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_MODEL_PLATFORM_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PLATFORM_MODEL_PLATFORM_HPP_

#include "../view/platform_view.hpp"
#include "shared_pointer.hpp"
#include "../../loop/objects/game_object.hpp"

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
