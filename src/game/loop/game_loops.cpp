#include <future>
#include "game_loops.hpp"

GameLoops::GameLoops(std::vector<IGameLoop*> loops)
    : m_game_loops_(loops) { }

void GameLoops::Activate()
{
    while (true)
    {
        for (auto &loop: m_game_loops_)
        {
            if (!loop->IsActive())
                return;

            loop->Update();
        }
    }
}
