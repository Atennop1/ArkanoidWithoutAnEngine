#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_GAME_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_GAME_ROOT_GAME_HPP_

#include <genesis/rendering/window_references.hpp>
#include <genesis/loop/game_loop.hpp>

namespace arkanoid
{
class Game
{
public:
    explicit Game(const genesis::WindowReferences &window_references);

    void Activate();

private:
    genesis::SharedPointer<genesis::GameLoop> game_loop_;
};
}

#endif
