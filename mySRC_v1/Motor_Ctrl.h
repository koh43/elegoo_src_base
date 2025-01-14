#ifndef MOTOR_CTRL_H
#define MOTOR_CTRL_H

#include <Arduino.h>

constexpr uint8_t PWM_PIN_STBY = 3;
constexpr uint8_t PWM_PIN_R = 5;
constexpr uint8_t PWM_PIN_L = 6;
/*
PINs for controlling the direction of the 
motor rotations.
HIGH: Forward
LOW: Backward
*/
constexpr uint8_t DIR_PIN_R = 7;
constexpr uint8_t DIR_PIN_L = 8;

class Motor_Ctrl {
public:
    Motor_Ctrl();
    ~Motor_Ctrl();
    void Init();
    void Move(
        const char& side,
        const bool& rot_dir,
        const uint8_t& speed
        // bool dir_flag_R,
        // bool move_flag_R,
        // uint8_t speed_R
    );
};

#endif // MOTOR_CTRL_H