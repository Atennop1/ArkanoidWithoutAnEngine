#ifndef ARKANOIDWITHOUTANENGINE_E9C0A2433A2C4C0BB13EFE96C306E795
#define ARKANOIDWITHOUTANENGINE_E9C0A2433A2C4C0BB13EFE96C306E795

class IReadOnlyGameTime
{
public:
    bool IsActive = true;
    virtual float Delta() = 0;

    virtual ~IReadOnlyGameTime() = default;
};

#endif
