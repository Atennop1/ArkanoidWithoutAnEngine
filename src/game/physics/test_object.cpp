#include "game/physics/test_object.hpp"
#include "game/shortcuts/shortcuts.hpp"
#include "game/shortcuts/render_colors.hpp"

namespace arkanoid
{
TestObject::TestObject(PhysicalProperties properties, WindowReferences references)
    : IGameObject(properties), references_(references) { }

void TestObject::Update(float delta)
{
    SDL_Rect rect = Shortcuts::PhysicalPropertiesToRect(Properties());
    Shortcuts::SelectColor(references_.Renderer(), RenderColors::kWhiteColor);
    SDL_RenderDrawRect(references_.Renderer(), &rect);
}

void TestObject::HandleCollisionStart(IPhysicsObject *other)
{
    Properties().velocity.x *= -1;
}
}