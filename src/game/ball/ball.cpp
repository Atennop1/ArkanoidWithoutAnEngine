#include "game/ball/ball.hpp"
#include "game/level/brick.hpp"

namespace arkanoid
{
Ball::Ball(PhysicalProperties properties, SharedPointer<BallView> ball_view)
    : IGameObject(properties), ball_view_(ball_view) { }

void Ball::Update(float delta)
{
    ball_view_->Display(Properties().position);
}

void Ball::HandleCollisionStart(IPhysicsObject *other)
{
    if (Brick* brick = dynamic_cast<Brick*>(other); brick != nullptr)
    {
        brick->Destroy();

    }
}
}
