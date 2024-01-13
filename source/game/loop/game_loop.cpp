#include <algorithm>
#include <stdexcept>
#include "game_loop.h"
#include "SDL.h"

void GameLoop::AddUpdatable(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) != m_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.push_back(updatable);
}

void GameLoop::RemoveUpdatable(const IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) == m_updatables_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    std::remove(m_updatables_.begin(), m_updatables_.end(), updatable);
}

GameLoop::GameLoop()
{
    m_updatables_ = std::list<IUpdatable*>();
}

GameLoop::GameLoop(const std::list<IUpdatable*> &updatables)
{
    m_updatables_ = updatables;
}

GameLoop::~GameLoop()
{
    for (IUpdatable* updatable : m_updatables_)
        free(updatable);
}

void GameLoop::Activate() const
{
    SDL_Event event;
    float delta;

    unsigned long long last_time;
    unsigned long long current_time = SDL_GetPerformanceCounter();

    while (true)
    {
        last_time = current_time;
        current_time = SDL_GetPerformanceCounter();
        delta = (float)(current_time - last_time) / (float)SDL_GetPerformanceFrequency(); // in seconds

        for (IUpdatable *updatable : m_updatables_)
            updatable->Update(delta);

        if (event.type == SDL_QUIT)
            break;
    }
}
