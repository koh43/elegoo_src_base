#include "SmartCar.h"

// Constructor
SmartCar::SmartCar(
    Servo& servo,
    uint8_t servo_pin
)
: servo_ctrl_(servo) {

}

// Destructor
SmartCar::~SmartCar() {
    
}

// Ultrasonic
bool SmartCar::get_us_dist(float* us_dist) {
    return us_.get_sensor_data(us_dist);
}

// IR remote controller
bool SmartCar::get_ir_rm_ctrl_input(IRrecv& irrecv, decode_results& results, uint8_t* ir_rm_ctrl_data) {
    return ir_recv_.get_sensor_data(irrecv, results, ir_rm_ctrl_data);
}

// Servo Control

void SmartCar::servo_reset() {
    servo_ctrl_.Reset();
}

void SmartCar::servo_move_to(uint8_t angle) {
    servo_ctrl_.MoveTo(angle);
}

void SmartCar::servo_update() {
    servo_ctrl_.Update();
}

uint8_t SmartCar::servo_get_angle() {
    return servo_ctrl_.GetAngle();
}

void SmartCar::servo_turn_left() {
    servo_ctrl_.TurnLeft();
}

void SmartCar::servo_turn_right() {
    servo_ctrl_.TurnRight();
}