#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include "ConstConfig.h"

class Ultrasonic {
public:
    Ultrasonic();
    ~Ultrasonic();
    void Init();
    bool Distance(float* us_dist);
};

#endif // ULTRASONIC_H