#ifndef SMART_CAR_H
#define SMART_CAR_H

#include "Ultrasonic.h"

class SmartCar {
public:
    // Constructor and Destructor
    SmartCar();
    ~SmartCar();

    // Initialization
    void SmartCarInit();

    // Ultrasonic (US)
    float get_us_dist();

private:
    // Declare sensor objects
    Ultrasonic us_;
};

#endif // SMART_CAR_H