#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_OBJECTS_GAME_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_OBJECTS_GAME_OBJECT_HPP_

#include "game_loop_object.hpp"
#include "../../physics/physics_object.h"

namespace arkanoid
{
class IGameObject : public IGameLoopObject, public IPhysicsObject
{
private:
    Vector2 m_position_;

public:
    virtual ~IGameObject() = default;
    virtual void Update(float delta) { };

    virtual void FixedUpdate(float fixed_delta) { };
    virtual void HandleCollisionStart() { };

    Vector2 GetPosition() final { return m_position_; };
    void SetPosition(Vector2 position) final { m_position_ = position; };
};
}

#endif
