#ifndef ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A
#define ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A

#include "rendering/window_references/window_references.hpp"
#include "loop/game_loops.hpp"
#include <memory>

class Game
{
private:
    std::unique_ptr<GameLoops> m_game_loops_;

public:
    explicit Game(const std::shared_ptr<WindowReferences> &window_references);
    void Activate() const;
};

#endif
