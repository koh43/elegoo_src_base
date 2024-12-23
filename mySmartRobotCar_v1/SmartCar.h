#ifndef SMART_CAR_H
#define SMART_CAR_H

#include "ConstConfig.h"

#ifdef USE_ULTRASONIC
#include "Ultrasonic.h"
#endif

#ifdef USE_SERVO_CTRL
#include "Servo_Ctrl.h"
#endif

#ifdef USE_VOLTAGE
#include "Voltage.h"
#endif

#ifdef USE_LED_CTRL
#include "LED_ctrl.h"
#endif

#ifdef USE_KEY_DETECT
#include "Key_Detect.h"
#endif

class SmartCar {
// ========== public ==========
public:
// Constructor and Destructor
    SmartCar();
    ~SmartCar();
    void Init();

// Ultrasonic functions
#ifdef USE_ULTRASONIC
    bool get_us_dist(float* us_dist);
#endif

// IR remote controller functions
#ifdef USE_IR_RM_CTRL
#include "IR_receiver.h"
    bool get_ir_rm_ctrl_input(IRrecv& irrecv, decode_results& results, uint8_t* ir_rm_ctrl_data);
#endif

// Servo Control functions
#ifdef USE_SERVO_CTRL
    void servo_reset();
    void servo_move_to(uint8_t angle);
    void servo_update();
    uint8_t servo_get_angle();
    void servo_turn_left();
    void servo_turn_right();
#endif

// Voltage measurement
#ifdef USE_VOLTAGE
    void measure_voltage(float* out);
#endif

// LED Control
#ifdef USE_LED_CTRL
    void led_set_brightness(uint8_t brightness);
    void led_set_blink_period(int period);
    void led_set_color(uint8_t led_id, CRGB color);
    void led_set_color(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b);
    void led_turn_on(uint8_t led_id);
    void led_turn_off(uint8_t led_id);
    void led_blink(uint8_t led_id);
#endif

// Key Detection
#ifdef USE_KEY_DETECT
    void key_detect_update();
    void key_detect_get(uint8_t* key_data);
#endif

// ========== private ==========
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

#ifdef USE_VOLTAGE
    Voltage volt_;
#endif

#ifdef USE_LED_CTRL
    LED_Ctrl led_ctrl_;
#endif

#ifdef USE_KEY_DETECT
    Key_Detect key_detect_;
#endif

};

#endif // SMART_CAR_H