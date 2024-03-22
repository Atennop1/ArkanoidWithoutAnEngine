#ifndef ARKANOIDWITHOUTANENGINE_C498C6B2102C462D850E4ECD94B88812
#define ARKANOIDWITHOUTANENGINE_C498C6B2102C462D850E4ECD94B88812

#include "loop/game_loop.h"
#include "dtos/window_references/window_references.h"
#include <memory>

class Game
{
private:
    std::unique_ptr<GameLoop> m_game_loop_;
    std::unique_ptr<IReadOnlyGameTime> m_game_time_;

public:
    explicit Game(const WindowReferences &window_references);
    void Activate() const;
};

#endif
