#ifndef SERVO_CTRL_H
#define SERVO_CTRL_H

#include <Arduino.h>
#include <Servo.h>
#include "ConstConfig.h"

class Servo_Ctrl {
public:
    Servo_Ctrl(Servo& servo, uint8_t servo_pin);
    ~Servo_Ctrl();
    void Reset();
    void MoveTo(uint8_t angle);
    void Update();
    uint8_t GetAngle();
    void TurnLeft();
    void TurnRight();

private:
    Servo* servo_;
    uint8_t init_angle_ = SERVO_INIT_ANGLE;
    uint8_t prev_angle_;
    unsigned long last_time_;
    unsigned long duration_;
    bool move_flag_ = false;
};

#endif // SERVO_CTRL_H
