#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENTRY_POINT_APPLICATION_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENTRY_POINT_APPLICATION_HPP_

#include "game/root/game.hpp"

namespace arkanoid
{
class Application
{
public:
    Application();
    ~Application();

    void Activate();

private:
    genesis::WindowReferences window_references_ = genesis::WindowReferences(nullptr, nullptr);
    genesis::SharedPointer<Game> m_game_ = genesis::SharedPointer<Game>();
};
}

#endif
