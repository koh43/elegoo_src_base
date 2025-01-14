#include "Motor_Ctrl.h"

Motor_Ctrl::Motor_Ctrl() {}

Motor_Ctrl::~Motor_Ctrl() {
    pinMode(PWM_PIN_STBY, INPUT);
    pinMode(PWM_PIN_R, INPUT);
    pinMode(PWM_PIN_L, INPUT);
    pinMode(DIR_PIN_R, INPUT);
    pinMode(DIR_PIN_L, INPUT);
}

void Motor_Ctrl::Init() {
    pinMode(PWM_PIN_STBY, OUTPUT);
    pinMode(PWM_PIN_R, OUTPUT);
    pinMode(PWM_PIN_L, OUTPUT);
    pinMode(DIR_PIN_R, OUTPUT);
    pinMode(DIR_PIN_L, OUTPUT);
}

void Motor_Ctrl::Move(
    const char& side,
    const bool& rot_dir,
    const uint8_t& speed
) {
    if (tolower(side) == 'l') {
        digitalWrite(PWM_PIN_STBY, HIGH);
        if (rot_dir) {
            digitalWrite(DIR_PIN_L, HIGH);
            analogWrite(PWM_PIN_L, speed);
        }
        else {
            digitalWrite(DIR_PIN_L, LOW);
            analogWrite(PWM_PIN_L, speed);
        }
    }
    else if (tolower(side) == 'r') {
        digitalWrite(PWM_PIN_STBY, HIGH);
        if (rot_dir) {
            digitalWrite(DIR_PIN_R, HIGH);
            analogWrite(PWM_PIN_R, speed);
        }
        else {
            digitalWrite(DIR_PIN_R, LOW);
            analogWrite(PWM_PIN_R, speed);
        }
    }
    else {
        digitalWrite(PWM_PIN_STBY, LOW);
        analogWrite(PWM_PIN_L, 0);
        analogWrite(PWM_PIN_R, 0);
    }
}