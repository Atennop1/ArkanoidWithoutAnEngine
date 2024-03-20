#ifndef ARKANOIDWITHOUTANENGINE_44D9141BC18842C38125C68434DCEA08
#define ARKANOIDWITHOUTANENGINE_44D9141BC18842C38125C68434DCEA08

#include "../../game/game.h"
#include "../../game/dtos/window_references/window_references.h"

class Application
{
private:
    WindowReferences m_window_references_;
    Game m_game_;

public:
    Application();
    ~Application();

    void Activate() const;
};

#endif
