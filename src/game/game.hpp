#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_GAME_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_GAME_HPP_

#include "shared_pointer.hpp"
#include "rendering/window_references/window_references.hpp"
#include "loop/game_loop.hpp"

namespace arkanoid
{
class Game
{
private:
    SharedPointer<GameLoop> game_loop_;

public:
    explicit Game(const WindowReferences &window_references);

    void Activate();
};
}

#endif
