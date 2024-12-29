#ifndef SERVO_CTRL_H
#define SERVO_CTRL_H

#include <Servo.h>
#include <Arduino.h>

constexpr uint8_t SERVO_PIN = 10;
constexpr unsigned int SERVO_DEGREE_ZERO_POS = 500;
constexpr unsigned int SERVO_DEGREE_PI_POS = 2400;
constexpr uint8_t SERVO_INIT_ANGLE = 90;
constexpr uint8_t SERVO_MIN_DEGREE = 0;
constexpr uint8_t SERVO_MAX_DEGREE = 180;
constexpr float SERVO_SPEED = 90 / 500; // 90 degrees per 500ms

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
