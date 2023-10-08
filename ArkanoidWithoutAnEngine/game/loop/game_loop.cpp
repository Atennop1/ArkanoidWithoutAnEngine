#include "game_loop.h"

#include <string>
#include <thread>
#include "../Converters/Converters.h"
#include "../shortcuts/shortcuts.h"

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
            if (message.message == WM_QUIT)
                goto OutOfLoop;

            TranslateMessage(&message);
            DispatchMessage(&message);

            for (IUpdatable* updatable : m_updatables_)
                updatable->Update(delta);
        }
    }

    OutOfLoop:;
}

//----------------------------------------------------------------------------------------------------
void GameLoop::Add(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) != m_updatables_.end())
        throw std::exception("Updatable already in loop");

    m_updatables_.push_front(updatable);
}

//----------------------------------------------------------------------------------------------------
void GameLoop::Remove(IUpdatable *updatable)
{
    if (std::find(m_updatables_.begin(), m_updatables_.end(), updatable) == m_updatables_.end())
        throw std::exception("Updatable doesn't in loop");

    std::remove(m_updatables_.begin(), m_updatables_.end(), updatable);
}

//----------------------------------------------------------------------------------------------------
GameLoop::GameLoop()
{
    m_updatables_ = std::list<IUpdatable*>();
}

//----------------------------------------------------------------------------------------------------
GameLoop::GameLoop(const std::list<IUpdatable*> *updatables)
{
    m_updatables_ = *updatables;
}

//----------------------------------------------------------------------------------------------------
GameLoop::~GameLoop()
{
    for (IUpdatable* updatable : m_updatables_)
        free(updatable);
}

//----------------------------------------------------------------------------------------------------
