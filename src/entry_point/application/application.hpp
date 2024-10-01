#ifndef ARKANOIDWITHOUTANENGINE_SRC_ENTRY_POINT_APPLICATION_APPLICATION_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_ENTRY_POINT_APPLICATION_APPLICATION_HPP_

#include "../../game/game.hpp"
#include "../../game/rendering//window_references/window_references.hpp"

namespace arkanoid
{
    class Application
    {
    private:
        WindowReferences window_references_ = WindowReferences(nullptr, nullptr);
        SharedPointer<Game> m_game_ = SharedPointer<Game>();

    public:
        Application();
        ~Application();

        void Activate();
    };
}

#endif
