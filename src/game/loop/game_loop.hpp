#ifndef ARKANOIDWITHOUTANENGINE_F758A52486FF46C9B146E6C930ED0432
#define ARKANOIDWITHOUTANENGINE_F758A52486FF46C9B146E6C930ED0432

class IGameLoop
{
public:
    virtual ~IGameLoop() = default;
    virtual void Update() = 0;
    virtual bool IsActive() = 0;
};

#endif
