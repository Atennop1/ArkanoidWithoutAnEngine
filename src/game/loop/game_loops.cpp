#include <future>
#include "game_loops.hpp"

GameLoops::GameLoops(std::vector<std::unique_ptr<IGameLoop>> &loops)
    : m_game_loops_(std::move(loops)) { }

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
