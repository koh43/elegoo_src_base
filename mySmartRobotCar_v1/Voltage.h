#ifndef VOLTAGE_H
#define VOLTAGE_H

#include "ConstConfig.h"

class Voltage {
public:
    Voltage(uint8_t voltage_pin = VOLTAGE_PIN);
    ~Voltage();
    void Init();
    void GetVolt(float* volt);
private:
    uint8_t voltage_pin_;
};

#endif // VOLTAGE_H