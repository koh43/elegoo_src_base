#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(
    uint8_t trigPin, 
    uint8_t echoPin, 
    float sensor_speed, 
    float max_dist
): trigPin_(trigPin), echoPin_(echoPin), sensor_speed_(sensor_speed), max_dist_(max_dist) {}

Ultrasonic::~Ultrasonic() {}

void Ultrasonic::initialize() {
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

float Ultrasonic::get_sensor_data() {
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_, LOW);

    float duration = pulseIn(echoPin_, HIGH);
    float distance = duration*sensor_speed_/2; // (cm)
    if (distance > max_dist_) {
        return max_dist_;
    }
    else {
        return distance;
    }
}