#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_GAME_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_GAME_HPP_

#include "engine/rendering/window_references.hpp"
#include "engine/loop/game_loop.hpp"

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
