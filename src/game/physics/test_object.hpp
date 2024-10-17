#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_TEST_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_PHYSICS_TEST_OBJECT_HPP_

#include "../loop/objects/game_object.hpp"
#include "../rendering/window_references/window_references.hpp"
namespace arkanoid
{
class TestObject : public IGameObject
{
public:
    TestObject(WindowReferences references);

    virtual void Update(float delta) override;

private:
    WindowReferences references_;
};
}

#endif
