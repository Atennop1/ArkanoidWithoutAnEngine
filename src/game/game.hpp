#ifndef ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A
#define ARKANOIDWITHOUTANENGINE_E0B1DD35A1FB4D53B48EB27BFA7B193A

#include "loop/game_loop.hpp"
#include "rendering/window_references/window_references.hpp"
#include <memory>

class Game
{
private:
    std::shared_ptr<IReadOnlyGameTime> m_game_time_;
    std::unique_ptr<GameLoop> m_game_loop_;

public:
    explicit Game(const std::shared_ptr<WindowReferences> &window_references);
    void Activate() const;
};

#endif
