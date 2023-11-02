#pragma once

#include "SDL.h"
#include "loop/game_loop.h"
#include "dtos/window_handles/window_references.h"

class Game
{
private:
    GameLoop *m_game_loop_;
    
public:
    Game(WindowReferences *window_references);
    ~Game();

    void Activate() const;
};

