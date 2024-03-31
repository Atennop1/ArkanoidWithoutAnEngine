#ifndef ARKANOIDWITHOUTANENGINE_C4ADACED5EB0489FA6179B7CADA25EA7
#define ARKANOIDWITHOUTANENGINE_C4ADACED5EB0489FA6179B7CADA25EA7

#include "../../game/game.hpp"
#include "../../game/rendering//window_references/window_references.hpp"

class Application
{
private:
    std::shared_ptr<WindowReferences> m_window_references_;
    std::unique_ptr<Game> m_game_;

public:
    Application();
    ~Application();

    void Activate() const;
};

#endif
