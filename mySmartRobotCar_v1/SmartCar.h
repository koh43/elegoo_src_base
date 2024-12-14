#ifndef SMART_CAR_H
#define SMART_CAR_H

#include "ConstConfig.h"

class SmartCar {

public:
// Constructor and Destructor
    SmartCar();
    ~SmartCar();
    void Init();

// Ultrasonic functions
#ifdef USE_ULTRASONIC
#include "Ultrasonic.h"
    bool get_us_dist(float* us_dist);
#endif

// IR remote controller functions
#ifdef USE_IR_RM_CTRL
#include "IR_receiver.h"
    bool get_ir_rm_ctrl_input(IRrecv& irrecv, decode_results& results, uint8_t* ir_rm_ctrl_data);
#endif

// Servo Control functions
#ifdef USE_SERVO_CTRL
#include "Servo_Ctrl.h"
    void servo_reset();
    void servo_move_to(uint8_t angle);
    void servo_update();
    uint8_t servo_get_angle();
    void servo_turn_left();
    void servo_turn_right();
#endif

// Voltage measurement
#ifdef USE_VOLTAGE

#endif

private:
#ifdef USE_ULTRASONIC 
    Ultrasonic us_;
#endif

#ifdef USE_IR_RM_CTRL
    IR_receiver* ir_recv_;
#endif

#ifdef USE_SERVO_CTRL
    Servo_Ctrl* servo_ctrl_;
#endif
};

#endif // SMART_CAR_H