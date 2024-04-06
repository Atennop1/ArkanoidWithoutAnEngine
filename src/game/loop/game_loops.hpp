#ifndef ARKANOIDWITHOUTANENGINE_3D238D9CAA64468ABA6CC6BC5A480F1B
#define ARKANOIDWITHOUTANENGINE_3D238D9CAA64468ABA6CC6BC5A480F1B

#include <vector>
#include "game_loop.hpp"
#include "shared_pointer.hpp"

class GameLoops
{
private:
    std::vector<SharedPointer<IGameLoop>> m_game_loops_;

public:
    explicit GameLoops(std::vector<SharedPointer<IGameLoop>> loops);
    void Activate();
};


#endif
