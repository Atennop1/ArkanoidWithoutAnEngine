#ifndef ARKANOIDWITHOUTANENGINE_3D238D9CAA64468ABA6CC6BC5A480F1B
#define ARKANOIDWITHOUTANENGINE_3D238D9CAA64468ABA6CC6BC5A480F1B

#include <vector>
#include <memory>
#include "game_loop.hpp"

class GameLoops : public IGameLoop
{
private:
    std::vector<std::unique_ptr<IGameLoop>> m_game_loops;

public:
    explicit GameLoops(std::vector<std::unique_ptr<IGameLoop>> &loops);
    ~GameLoops() override = default;

    void Activate() override;
};


#endif
