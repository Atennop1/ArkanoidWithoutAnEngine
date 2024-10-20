#include "game/physics/test_object.hpp"

namespace arkanoid
{
TestObject::TestObject(PhysicalProperties properties, WindowReferences references)
    : IGameObject(properties), references_(references) { }

void TestObject::Update(float delta)
{
    SDL_Rect rect;
    rect.x = Properties().position.x;
    rect.y = Properties().position.y;
    rect.w = Properties().size.x;
    rect.h = Properties().size.y;

    SDL_SetRenderDrawColor(references_.Renderer(), 255, 255, 255, 255);
    SDL_RenderDrawRect(references_.Renderer(), &rect);
}

void TestObject::HandleCollisionStart(IPhysicsObject *other)
{
    Properties().velocity.x *= -1;
}
}