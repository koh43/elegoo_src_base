#include "./Ultrasonic.h"

Ultrasonic::Ultrasonic() {}

Ultrasonic::~Ultrasonic() {
    pinMode(ULTRASONIC_TRIG_PIN, INPUT);
}

void Ultrasonic::Init() {
    pinMode(ULTRASONIC_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

bool Ultrasonic::Distance(float* us_dist) {
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

    // Measure duration of echo signal with a timeout of 30ms
    float duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, 30000); // Timeout in microseconds
    if (duration <= 0) { // Handle no response or invalid signal
        *us_dist = -1;
        return false;
    }

    float distance = duration * ULTRASONIC_SENSOR_SPEED / 2; // (cm)
    
    if (distance > ULTRASONIC_MAX_DIST) {
        *us_dist = ULTRASONIC_MAX_DIST/100;
    }
    else {
        *us_dist = distance/100;
    }
    return true;
}