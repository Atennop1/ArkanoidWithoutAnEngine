#ifndef ARKANOIDWITHOUTANENGINE_INCLUDE_ENTRY_POINT_APPLICATION_HPP_
#define ARKANOIDWITHOUTANENGINE_INCLUDE_ENTRY_POINT_APPLICATION_HPP_

#include "game/rendering/window_references.hpp"
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
    WindowReferences window_references_ = WindowReferences(nullptr, nullptr);
    SharedPointer<Game> m_game_ = SharedPointer<Game>();
};
}

#endif
