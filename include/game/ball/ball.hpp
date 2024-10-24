#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_HPP_

#include "game/loop/objects/game_object.hpp"
#include "tools/shared_pointer.hpp"
#include "ball_view.hpp"

namespace arkanoid
{
class Ball : public IGameObject
{
public:
    Ball(PhysicalProperties properties, SharedPointer<BallView> ball_view);

    void Update(float delta);
    void HandleCollisionStart(IPhysicsObject *other) override;

private:
    SharedPointer<BallView> ball_view_;
};
}

#endif
