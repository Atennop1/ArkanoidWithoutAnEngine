#ifndef ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_GAME_LOOP_OBJECT_HPP_
#define ARKANOIDWITHOUTANENGINE_SRC_GAME_LOOP_GAME_LOOP_OBJECT_HPP_

namespace arkanoid
{
    class IGameLoopObject
    {
    public:
        virtual ~IGameLoopObject() = default;

        virtual void Update(float delta) = 0;
    };
}

#endif
