#ifndef IVEHICLE_H
#define IVEHICLE_H

class IVehicle {
public:
    virtual ~IVehicle() {}
    virtual unsigned int getId() = 0;
    virtual int getPriority() = 0;
    virtual float getSpeed() = 0;
};

#endif // IVEHICLE_H
