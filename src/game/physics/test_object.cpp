#include "test_object.hpp"

namespace arkanoid
{
TestObject::TestObject(WindowReferences references)
    : references_(references) { }

void TestObject::Update(float delta)
{
    SDL_Rect rect;
    rect.x = Position().X();
    rect.y = Position().Y();
    rect.w = Size().X();
    rect.h = Size().Y();

    SDL_SetRenderDrawColor(references_.Renderer(), 255, 255, 255, 255);
    SDL_RenderDrawRect(references_.Renderer(), &rect);
}
}