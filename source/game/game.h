#pragma once

#include "SDL.h"
#include "loop/game_loop.h"
#include "dtos/window_references/window_references.h"

class Game
{
private:
    GameLoop *m_game_loop_;

public:
    explicit Game(const WindowReferences &window_references);
    ~Game();

    void Activate() const;
};

