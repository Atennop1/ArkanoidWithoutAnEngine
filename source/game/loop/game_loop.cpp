#include <string>
#include <thread>
#include "game_loop.h"

//----------------------------------------------------------------------------------------------------
void GameLoop::Activate() const
{
    MSG message;
    LARGE_INTEGER current_counter;

    LARGE_INTEGER cpu_frequency;
    LARGE_INTEGER last_counter;
    
    QueryPerformanceFrequency(&cpu_frequency);
    QueryPerformanceCounter(&last_counter);

    while (true)
    {
        QueryPerformanceCounter(&current_counter);
        const int64_t counter_elapsed = current_counter.QuadPart - last_counter.QuadPart;

        const float delta = (float)counter_elapsed / (float)cpu_frequency.QuadPart;
        last_counter = current_counter;
        
        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);

            for (ISystemUpdatable *system_updatable : m_system_updatables_)
                system_updatable->Update(&message);
        }
        
        for (IUpdatable *updatable : m_updatables_)
            updatable->Update(delta);
        
        if (message.message == WM_QUIT)
            break;
    }
}

//----------------------------------------------------------------------------------------------------
void GameLoop::AddUpdatable(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) != m_updatables_.end())
        throw std::exception("Updatable already in loop");

    m_updatables_.push_back(updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::RemoveUpdatable(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) == m_updatables_.end())
        throw std::exception("Updatable doesn't in loop");

    std::remove(m_updatables_.begin(), m_updatables_.end(), updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::AddSystemUpdatable(ISystemUpdatable *updatable)
{
    if (std::find(m_system_updatables_.begin(), m_system_updatables_.end(), updatable) != m_system_updatables_.end())
        throw std::exception("SystemUpdatable already in loop");

    m_system_updatables_.push_back(updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::RemoveSystemUpdatable(ISystemUpdatable *updatable)
{
    if (std::find(m_system_updatables_.begin(), m_system_updatables_.end(), updatable) == m_system_updatables_.end())
        throw std::exception("SystemUpdatable doesn't in loop");

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
