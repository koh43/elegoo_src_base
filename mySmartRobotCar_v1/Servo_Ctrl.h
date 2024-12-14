#ifndef SERVO_CTRL_H
#define SERVO_CTRL_H

#include <Servo.h>
#include <Arduino.h>
#include "ConstConfig.h"

class Servo_Ctrl {
public:
    Servo_Ctrl(Servo& servo);
    ~Servo_Ctrl();
    void Init();
    void Reset();
    void MoveTo(uint8_t angle);
    void Update();
    uint8_t GetAngle();
    void TurnLeft();
    void TurnRight();

private:
    Servo* servo_;
    uint8_t prev_angle_;
    unsigned long last_time_;
    unsigned long duration_;
    bool move_flag_ = false;
};

#endif // SERVO_CTRL_H
