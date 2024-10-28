#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_INPUT_INPUT_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENGINE_EVENTS_INPUT_INPUT_HPP_

#include "key_type.hpp"
#include "engine/loop/objects/game_loop_object.hpp"
#include "engine/events/application_events.hpp"
#include "tools/shared_pointer.hpp"
#include <list>

namespace arkanoid
{
class Input : public IGameLoopObject
{
public:
    Input(const SharedPointer<ApplicationEvents> &events);

    void Update(float delta) override;
    bool IsKeyPressed(KeyType key_type) const;
    bool IsKeyPressedThisFrame(KeyType key_type) const;

private:
    std::list<KeyType> pressed_keys_ = { };
    std::list<KeyType> pressed_this_frame_keys_ = { };
    SharedPointer<ApplicationEvents> events_;
};
}

#endif
