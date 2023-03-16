#ifndef ISIGNAL_H
#define ISIGNAL_H

class ISignal
{
public:
    virtual ~ISignal() {}
    virtual bool isRed() = 0;
    virtual bool isGreen() = 0;
};

#endif // ISIGNAL_H
