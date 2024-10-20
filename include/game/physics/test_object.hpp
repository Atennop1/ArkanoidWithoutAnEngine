#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_TEST_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_PHYSICS_TEST_OBJECT_HPP_

#include "physical_properties.hpp"
#include "physics_object.hpp"
#include "game/loop/objects/game_object.hpp"
#include "game/rendering/window_references.hpp"

namespace arkanoid
{
class TestObject : public IGameObject
{
public:
    TestObject(PhysicalProperties properties, WindowReferences references);

    virtual void Update(float delta) override;
    virtual void HandleCollisionStart(IPhysicsObject* other) override;

private:
    WindowReferences references_;
};
}

#endif
