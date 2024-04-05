#ifndef ARKANOIDWITHOUTANENGINE_3D238D9CAA64468ABA6CC6BC5A480F1B
#define ARKANOIDWITHOUTANENGINE_3D238D9CAA64468ABA6CC6BC5A480F1B

#include <vector>
#include <memory>
#include "game_loop.hpp"

class GameLoops
{
private:
    std::vector<IGameLoop*> m_game_loops_;

public:
    explicit GameLoops(std::vector<IGameLoop*> loops);
    void Activate();
};


#endif
