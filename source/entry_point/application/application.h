#pragma once
#include "../../game/game.h"
#include "../../game/dtos/window_handles/window_references.h"

class Application
{
private:
    WindowReferences *m_window_references_;
    Game *m_game_;
    
public:
    Application();
    ~Application();
    
    void Activate() const;
};
