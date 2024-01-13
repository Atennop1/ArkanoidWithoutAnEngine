#pragma once

#include <list>
#include "updatable.h"

class GameLoop
{
private:
    std::list<IUpdatable*> m_updatables_;
    
public:
    GameLoop();
    explicit GameLoop(const std::list<IUpdatable*> &updatables);
    ~GameLoop();
    
    void AddUpdatable(IUpdatable *updatable);
    void RemoveUpdatable(const IUpdatable *updatable);

    void Activate() const;
};
