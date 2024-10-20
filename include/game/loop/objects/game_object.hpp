#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LOOP_OBJECTS_GAME_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_LOOP_OBJECTS_GAME_OBJECT_HPP_

#include "game_loop_object.hpp"
#include "game/physics/physical_properties.hpp"
#include "game/physics/physics_object.hpp"

namespace arkanoid
{
class IGameObject : public IGameLoopObject, public IPhysicsObject
{
public:
    IGameObject(PhysicalProperties properties) : properties_(properties) { }
    virtual ~IGameObject() = default;

    virtual void Update(float delta) { }
    virtual void FixedUpdate(float fixed_delta) { }

    virtual void HandleCollisionStart(IPhysicsObject* other) { }
    virtual PhysicalProperties& Properties() { return properties_; }

private:
    PhysicalProperties properties_;
};
}

#endif
