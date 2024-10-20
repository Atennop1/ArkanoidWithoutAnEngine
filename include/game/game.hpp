#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_GAME_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_GAME_HPP_

#include "tools/shared_pointer.hpp"
#include "rendering/window_references.hpp"
#include "loop/game_loop.hpp"

namespace arkanoid
{
class Game
{
public:
    explicit Game(const WindowReferences &window_references);

    void Activate();

private:
    SharedPointer<GameLoop> game_loop_;
};
}

#endif
