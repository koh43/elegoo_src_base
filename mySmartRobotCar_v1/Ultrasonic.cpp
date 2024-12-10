#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(
    uint8_t trigPin, 
    uint8_t echoPin, 
    float sensor_speed, 
    float max_dist
):
trigPin_(trigPin), echoPin_(echoPin), sensor_speed_(sensor_speed), max_dist_(max_dist) {
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

Ultrasonic::~Ultrasonic() {}

bool Ultrasonic::get_sensor_data(float* us_dist) {
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_, LOW);

    // Measure duration of echo signal with a timeout of 30ms
    float duration = pulseIn(echoPin_, HIGH, 30000); // Timeout in microseconds
    if (duration <= 0) { // Handle no response or invalid signal
        *us_dist = -1;
        return false;
    }

    float distance = duration*sensor_speed_/2; // (cm)
    
    if (distance > max_dist_) {
        *us_dist = max_dist_;
    }
    else {
        *us_dist = distance;        
    }
    return true;
}