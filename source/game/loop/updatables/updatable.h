#ifndef ARKANOIDWITHOUTANENGINE_F4FD595B2B8D4DFE9E36CBB20A609690
#define ARKANOIDWITHOUTANENGINE_F4FD595B2B8D4DFE9E36CBB20A609690

class IUpdatable
{
public:
    virtual ~IUpdatable() = default;
    virtual void Update(float delta) = 0;
};

#endif
