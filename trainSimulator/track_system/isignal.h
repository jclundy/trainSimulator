#ifndef ISIGNAL_H
#define ISIGNAL_H

class ISignal
{
public:
    virtual ~ISignal() {}
    virtual bool isRed() = 0;
    virtual bool isGreen() = 0;
    virtual void update() = 0;
};

#endif // ISIGNAL_H
