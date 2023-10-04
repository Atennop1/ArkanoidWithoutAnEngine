#pragma once

#include <list>
#include "updatable.h"

class GameLoop
{
private:
    std::list<IUpdatable*> m_updatables_;
    
public:
    GameLoop();
    GameLoop(const std::list<IUpdatable*> *updatables);
    ~GameLoop();
    
    void Add(IUpdatable *updatable);
    void Remove(IUpdatable *updatable);

    void Activate() const;
};
