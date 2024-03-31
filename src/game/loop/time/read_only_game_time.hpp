#ifndef ARKANOIDWITHOUTANENGINE_A0A0D9EF0A184C6DB6FF713603E29C83
#define ARKANOIDWITHOUTANENGINE_A0A0D9EF0A184C6DB6FF713603E29C83

class IReadOnlyGameTime
{
public:
    virtual bool IsActive() = 0;
    virtual float Delta() = 0;

    virtual ~IReadOnlyGameTime() = default;
};

#endif
