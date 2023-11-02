#include <algorithm>
#include <stdexcept>
#include "game_loop.h"
#include "SDL.h"

//----------------------------------------------------------------------------------------------------
void GameLoop::Activate() const
{
    float delta;
    unsigned long long last_time;
    unsigned long long current_time = SDL_GetPerformanceCounter();

    while (true)
    {
        last_time = current_time;
        current_time = SDL_GetPerformanceCounter();
        delta = (float)(current_time - last_time) * 1000 / (float)SDL_GetPerformanceFrequency(); // in milliseconds
        
        SDL_Event event;
        SDL_PollEvent(&event);

        for (ISystemUpdatable *system_updatable : m_system_updatables_)
            system_updatable->Update(event);
        
        for (IUpdatable *updatable : m_updatables_)
            updatable->Update(delta);
        
        if (event.type == SDL_QUIT)
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void GameLoop::AddUpdatable(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) != m_updatables_.end())
        throw std::invalid_argument("Updatable already in loop");

    m_updatables_.push_back(updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::RemoveUpdatable(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) == m_updatables_.end())
        throw std::invalid_argument("Updatable doesn't in loop");

    std::remove(m_updatables_.begin(), m_updatables_.end(), updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::AddSystemUpdatable(ISystemUpdatable *updatable)
{
    if (std::find(m_system_updatables_.begin(), m_system_updatables_.end(), updatable) != m_system_updatables_.end())
        throw std::invalid_argument("SystemUpdatable already in loop");

    m_system_updatables_.push_back(updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::RemoveSystemUpdatable(ISystemUpdatable *updatable)
{
    if (std::find(m_system_updatables_.begin(), m_system_updatables_.end(), updatable) == m_system_updatables_.end())
        throw std::invalid_argument("SystemUpdatable doesn't in loop");

    std::remove(m_system_updatables_.begin(), m_system_updatables_.end(), updatable);
}

//----------------------------------------------------------------------------------------------------
GameLoop::GameLoop()
{
    m_updatables_ = std::list<IUpdatable*>();
    m_system_updatables_ = std::list<ISystemUpdatable*>();
}

//----------------------------------------------------------------------------------------------------
GameLoop::GameLoop(const std::list<IUpdatable*> *updatables, const std::list<ISystemUpdatable*> *system_updatables)
{
    m_updatables_ = *updatables;
    m_system_updatables_ = *system_updatables;
}

//----------------------------------------------------------------------------------------------------
GameLoop::~GameLoop()
{
    for (ISystemUpdatable* system_updatable : m_system_updatables_)
        free(system_updatable);
    
    for (IUpdatable* updatable : m_updatables_)
        free(updatable);
}

//----------------------------------------------------------------------------------------------------
