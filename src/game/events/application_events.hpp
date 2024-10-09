#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_EVENTS_APPLICATION_EVENTS_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_EVENTS_APPLICATION_EVENTS_HPP_

#include "../loop/objects/game_loop_object.hpp"
#include <SDL.h>
#include <list>
#include <vector>

namespace arkanoid
{
class ApplicationEvents : public IGameLoopObject
{
private:
    std::list<SDL_Event> events_ = {};

public:
    ~ApplicationEvents() override = default;
    void Update(float delta) override;

    std::vector<SDL_Event *> GetEventsOfType(Uint32 type) { return GetEventsOfType(std::vector<Uint32>{type}); }
    std::vector<SDL_Event *> GetEventsOfType(std::vector<Uint32> types);
};
}

#endif