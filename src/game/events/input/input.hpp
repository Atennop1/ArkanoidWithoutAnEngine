#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_EVENTS_INPUT_INPUT_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_EVENTS_INPUT_INPUT_HPP_

#include "key_type.hpp"
#include "../../loop/objects/game_loop_object.hpp"
#include "../application_events.hpp"
#include "shared_pointer.hpp"
#include "SDL.h"
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
