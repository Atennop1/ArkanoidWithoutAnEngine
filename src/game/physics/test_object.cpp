#include "test_object.hpp"

namespace arkanoid
{
TestObject::TestObject(PhysicalProperties properties, WindowReferences references)
    : IGameObject(properties), references_(references) { }

void TestObject::Update(float delta)
{
    SDL_Rect rect;
    rect.x = Properties().position.X();
    rect.y = Properties().position.Y();
    rect.w = Properties().size.X();
    rect.h = Properties().size.Y();

    SDL_SetRenderDrawColor(references_.Renderer(), 255, 255, 255, 255);
    SDL_RenderDrawRect(references_.Renderer(), &rect);
}

void TestObject::HandleCollisionStart(IPhysicsObject *other)
{
    Properties().velocity = Vector2(-Properties().velocity.X(), Properties().velocity.Y());
}
}