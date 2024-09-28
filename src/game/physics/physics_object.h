#ifndef ARKANOIDWITHOUTANENGINE_C0C9FA8FC78B43F48B156C24C28FA06F
#define ARKANOIDWITHOUTANENGINE_C0C9FA8FC78B43F48B156C24C28FA06F

namespace arkanoid
{
    class IPhysicsObject
    {
    public:
        virtual ~IPhysicsObject() = default;

        virtual void FixedUpdate(float fixed_delta) = 0;
    };
}

#endif
