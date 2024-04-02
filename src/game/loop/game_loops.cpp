#include <future>
#include "game_loops.hpp"

GameLoops::GameLoops(std::vector<std::unique_ptr<IGameLoop>> &loops)
    : m_game_loops(std::move(loops)) { }

void GameLoops::Activate()
{
    for (auto &loop : m_game_loops)
        loop->Activate();
}
