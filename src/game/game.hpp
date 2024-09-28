#ifndef ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A
#define ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A

#include "shared_pointer.hpp"
#include "rendering/window_references/window_references.hpp"
#include "loop/game_loop.hpp"

namespace arkanoid
{
    class Game
    {
    private:
        SharedPointer<GameLoop> m_game_loop_;

    public:
        explicit Game(const WindowReferences &window_references);

        void Activate();
    };
}

#endif
