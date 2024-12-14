#include "SmartCar.h"

#ifdef USE_IR_RM_CTRL
IRrecv irrecv(IR_RECEIVER_PIN); //  Create an infrared receive drive object
decode_results dr;
IR_receiver ir_recv(irrecv, dr);
#endif

#ifdef USE_SERVO_CTRL
Servo servo;
Servo_Ctrl servo_ctrl(servo);
#endif

// Constructor
SmartCar::SmartCar() {
#ifdef USE_IR_RM_CTRL
    ir_recv_ = &ir_recv;
    dr_ = &dr;
#endif
#ifdef USE_SERVO_CTRL
    servo_ctrl_ = &servo_ctrl;
#endif
}

// Destructor
SmartCar::~SmartCar() {
#ifdef USE_ULTRASONIC
    us_.~Ultrasonic();
#endif
#ifdef USE_IR_RM_CTRL
    ir_recv_->~IR_receiver();
#endif
#ifdef USE_SERVO_CTRL
    servo_ctrl_->~Servo_Ctrl();
#endif
}

// Initialize the sensors
void SmartCar::Init() {
#ifdef USE_ULTRASONIC
    us_.Init();
#endif
#ifdef USE_IR_RM_CTRL
    ir_recv_->Init();
#endif
#ifdef USE_SERVO_CTRL
    servo_ctrl_->Init(SERVO_PIN);
#endif
}

// Ultrasonic
#ifdef USE_ULTRASONIC
bool SmartCar::get_us_dist(float* us_dist) {
    return us_.Distance(us_dist);
}
#endif

// IR remote controller
#ifdef USE_IR_RM_CTRL
bool SmartCar::get_ir_rm_ctrl_input(uint8_t* ir_rm_ctrl_data) {
    return ir_recv_.get_sensor_data(ir_rm_ctrl_data);
}
#endif

// Servo Control

void SmartCar::servo_reset() {
    servo_ctrl_->Reset();
}

void SmartCar::servo_move_to(uint8_t angle) {
    servo_ctrl_->MoveTo(angle);
}

void SmartCar::servo_update() {
    servo_ctrl_->Update();
}

uint8_t SmartCar::servo_get_angle() {
    return servo_ctrl_->GetAngle();
}

void SmartCar::servo_turn_left() {
    servo_ctrl_->TurnLeft();
}

void SmartCar::servo_turn_right() {
    servo_ctrl_->TurnRight();
}