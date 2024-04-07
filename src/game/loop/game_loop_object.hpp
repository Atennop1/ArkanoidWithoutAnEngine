#ifndef ARKANOIDWITHOUTANENGINE_E24C4625CAEA429C98529442DC20F6EB
#define ARKANOIDWITHOUTANENGINE_E24C4625CAEA429C98529442DC20F6EB

class IGameLoopObject
{
public:
    virtual ~IGameLoopObject() = default;
    virtual void Update(float delta) = 0;
};

#endif
