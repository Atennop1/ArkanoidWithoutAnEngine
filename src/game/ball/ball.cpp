#include "game/ball/ball.hpp"
#include "game/level/brick.hpp"
#include "game/platform/platform.hpp"

namespace arkanoid
{
Ball::Ball(genesis::PhysicalProperties properties, genesis::SharedPointer<BallView> ball_view)
    : IGameObject(properties), ball_view_(ball_view) { }

void Ball::Update(float delta)
{
    ball_view_->Display(Properties().position);
}

void Ball::HandleCollisionStart(IPhysicsObject *other)
{
    if (Brick* brick = dynamic_cast<Brick*>(other); brick != nullptr)
        brick->Destroy();

    float overlap_left = Properties().Right() - other->Properties().Left();
    float overlap_right = other->Properties().Right() - Properties().Left();
    float overlap_top = Properties().Bottom() - other->Properties().Top();
    float overlap_bottom = other->Properties().Bottom() - Properties().Top();

    bool ball_from_left = fabs(overlap_left) < fabs(overlap_right);
    bool ball_from_top = fabs(overlap_top) < fabs(overlap_bottom);

    float min_overlap_x = ball_from_left ? overlap_left : overlap_right;
    float min_overlap_y = ball_from_top ? overlap_top : overlap_bottom;

    if (dynamic_cast<Platform*>(other) != nullptr)
    {
        Properties().velocity.x = fabs(Properties().velocity.x) * (Properties().position.x < other->Properties().position.x ? -1 : 1);
        Properties().velocity.y = fabs(Properties().velocity.y) * (ball_from_top && fabs(min_overlap_x) >= fabs(min_overlap_y) ? -1 : 1);
        return;
    }

    if (fabs(min_overlap_x) <= fabs(min_overlap_y)) { Properties().velocity.x = fabs(Properties().velocity.x) * (ball_from_left ? -1 : 1); }
    else { Properties().velocity.y = fabs(Properties().velocity.y) * (ball_from_top ? -1 : 1); }
}
}
