#ifndef ARKANOIDWITHOUTANENGINE_C0C9FA8FC78B43F48B156C24C28FA06F
#define ARKANOIDWITHOUTANENGINE_C0C9FA8FC78B43F48B156C24C28FA06F

class IPhysicsObject
{
public:
    virtual ~IPhysicsObject() = default;
    virtual void FixedUpdate(float delta) = 0;
};

#endif
