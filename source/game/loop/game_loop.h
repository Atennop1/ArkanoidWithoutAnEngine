#pragma once

#include <list>
#include "updatables/updatable.h"
#include "updatables/system_updatable.h"

class GameLoop
{
private:
    std::list<IUpdatable*> m_updatables_;
    std::list<ISystemUpdatable*> m_system_updatables_;
    
public:
    GameLoop();
    GameLoop(const std::list<IUpdatable*> *updatables, const std::list<ISystemUpdatable*> *system_updatables);
    ~GameLoop();
    
    void AddUpdatable(IUpdatable *updatable);
    void RemoveUpdatable(IUpdatable *updatable);

    void AddSystemUpdatable(ISystemUpdatable *updatable);
    void RemoveSystemUpdatable(ISystemUpdatable *updatable);

    void Activate() const;
};
