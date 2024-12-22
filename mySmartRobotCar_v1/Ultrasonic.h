#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

constexpr float   ULTRASONIC_SENSOR_SPEED = 0.0343; // (cm / microsec)
constexpr uint8_t ULTRASONIC_TRIG_PIN = 13;
constexpr uint8_t ULTRASONIC_ECHO_PIN = 12;
constexpr float   ULTRASONIC_MAX_DIST = 400.0; // (cm)

class Ultrasonic {
public:
    Ultrasonic();
    ~Ultrasonic();
    void Init();
    bool Distance(float* us_dist);
};

#endif // ULTRASONIC_H