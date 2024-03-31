#ifndef ARKANOIDWITHOUTANENGINE_E4E256ED49C240E0BCE81BAAB2058349
#define ARKANOIDWITHOUTANENGINE_E4E256ED49C240E0BCE81BAAB2058349

class IUpdatable
{
public:
    virtual ~IUpdatable() = default;
    virtual void Update(float delta) = 0;
};

#endif
