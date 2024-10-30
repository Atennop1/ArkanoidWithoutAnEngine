#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_BALL_BALL_HPP_

#include "genesis/memory/shared_pointer.hpp"
#include "genesis/loop/objects/game_object.hpp"
#include "ball_view.hpp"

namespace arkanoid
{
class Ball : public genesis::IGameObject
{
public:
    Ball(genesis::PhysicalProperties properties, genesis::SharedPointer<BallView> ball_view);

    virtual void Update(float delta) override;
    void HandleCollisionStart(genesis::IPhysicsObject *other) override;

private:
    genesis::SharedPointer<BallView> ball_view_;
};
}

#endif
