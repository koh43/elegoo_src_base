#ifndef SMART_CAR_H
#define SMART_CAR_H

#include "Ultrasonic.h"
#include "IR_receiver.h"
#include "Servo_Ctrl.h"

class SmartCar {
public:
    // Constructor and Destructor
    SmartCar(
        Servo& servo,
        uint8_t servo_pin = SERVO_PIN
    );
    ~SmartCar();

    // Ultrasonic (US)
    bool get_us_dist(float* us_dist);

    // IR remote controller input
    bool get_ir_rm_ctrl_input(IRrecv& irrecv, decode_results& results, uint8_t* ir_rm_ctrl_data);

    // Servo Control
    void servo_reset();
    void servo_move_to(uint8_t angle);
    void servo_update();
    uint8_t servo_get_angle();
    void servo_turn_left();
    void servo_turn_right();

private:
    // Declare sensor objects
    Ultrasonic us_;
    IR_receiver ir_recv_;
    Servo_Ctrl servo_ctrl_;
};

#endif // SMART_CAR_H