#ifndef ARKANOIDWITHOUTANENGINE_E24C4625CAEA429C98529442DC20F6EB
#define ARKANOIDWITHOUTANENGINE_E24C4625CAEA429C98529442DC20F6EB

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
