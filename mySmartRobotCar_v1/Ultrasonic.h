#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include "ConstConfig.h"

class Ultrasonic {
public:
    Ultrasonic(
        uint8_t trigPin = ULTRASONIC_TRIG_PIN,
        uint8_t echoPin = ULTRASONIC_ECHO_PIN,
        float   sensor_speed = ULTRASONIC_SENSOR_SPEED,
        float   max_dist = ULTRASONIC_MAX_DIST
    );
    ~Ultrasonic();
    void initialize();
    float get_sensor_data();

private:
    uint8_t trigPin_, echoPin_;
    float   sensor_speed_, max_dist_;
};

#endif // ULTRASONIC_H