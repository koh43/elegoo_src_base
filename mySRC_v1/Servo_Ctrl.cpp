#include "./Servo_Ctrl.h"

Servo_Ctrl::Servo_Ctrl(Servo& servo) : servo_(&servo) {
    
}

Servo_Ctrl::~Servo_Ctrl() {
    servo_->detach();
}

void Servo_Ctrl::Init() {
    servo_->attach(
        SERVO_PIN,
        SERVO_DEGREE_ZERO_POS,
        SERVO_DEGREE_PI_POS
    );
    MoveTo(SERVO_INIT_ANGLE);
}

void Servo_Ctrl::Reset() {
    MoveTo(SERVO_INIT_ANGLE);
}

void Servo_Ctrl::MoveTo(uint8_t angle) {
    if (move_flag_) return;
    if (angle > SERVO_MAX_DEGREE) {
        Serial.println("Servo angle can't be greater than 180, setting to max degree.");
        angle = SERVO_MAX_DEGREE;
    }
    // Calculate the movement duration based on the speed and angle difference
    duration_ = abs(prev_angle_ - angle)/SERVO_SPEED;
    last_time_ = millis();
    move_flag_ = true;
    // Start the servo movement
    servo_->write(angle);
    prev_angle_ = angle;
}

void Servo_Ctrl::Update() {
    if (move_flag_ && millis() - last_time_ >= duration_) {
        move_flag_ = false;
    }
}

uint8_t Servo_Ctrl::GetAngle() {
    return prev_angle_;
}

void Servo_Ctrl::TurnLeft() {
    uint8_t servo_angle = GetAngle();
    if (servo_angle + 5 > SERVO_MAX_DEGREE) {
        servo_angle = SERVO_MAX_DEGREE;
    }
    else {
        servo_angle += 5;
    }
    MoveTo(servo_angle);
}

void Servo_Ctrl::TurnRight() {
    uint8_t servo_angle = GetAngle();
    if (servo_angle - 5 < SERVO_MIN_DEGREE) {
        servo_angle = SERVO_MIN_DEGREE;
    }
    else {
        servo_angle -= 5;
    }
    MoveTo(servo_angle);
}