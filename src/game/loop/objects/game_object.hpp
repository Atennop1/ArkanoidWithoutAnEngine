#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_OBJECTS_GAME_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_OBJECTS_GAME_OBJECT_HPP_

#include "game_loop_object.hpp"
#include "../../physics/physics_object.h"

namespace arkanoid
{
class IGameObject : public IGameLoopObject, public IPhysicsObject
{
private:
    Vector2 position_;
    Vector2 size_;

    Vector2 velocity_;
    Vector2 acceleration_;

public:
    virtual ~IGameObject() = default;

    virtual void Update(float delta) { };
    virtual void FixedUpdate(float fixed_delta) { };
    virtual void HandleCollisionStart(CollisionData data) { };


    Vector2 Position() final { return position_; };
    void SetPosition(Vector2 position) final { position_ = position; };

    Vector2 Size() final { return size_; };
    void SetSize(Vector2 size) final { size_ = size; };

    Vector2 Velocity() final { return velocity_; };
    void SetVelocity(Vector2 velocity) final { velocity_ = velocity; };

    Vector2 Acceleration() final { return acceleration_; };
    void SetAcceleration(Vector2 acceleration) final { acceleration_ = acceleration; };
};
}

#endif
