#ifndef ARKANOIDWITHOUTANENGINE_8552A448B33E47028D443609AD3E447A
#define ARKANOIDWITHOUTANENGINE_8552A448B33E47028D443609AD3E447A

#include "../loop/game_loop_object.hpp"
#include <SDL.h>
#include <list>
#include <vector>

namespace arkanoid
{
    class ApplicationEvents : public IGameLoopObject
    {
    private:
        std::list<SDL_Event> m_events_ = {};

    public:
        ~ApplicationEvents() override = default;

        void Update(float delta) override;

        std::vector<SDL_Event *> GetEventsOfType(Uint32 type)
        { return GetEventsOfType(std::vector<Uint32>{type}); }

        std::vector<SDL_Event *> GetEventsOfType(std::vector<Uint32> types);
    };
}

#endif