#ifndef SMART_CAR_H
#define SMART_CAR_H

#include "Config.h"

#ifdef USE_ULTRASONIC
#include "Ultrasonic.h"
#endif

#ifdef USE_IR_RM_CTRL
#include "IR_Receiver.h"
#endif

#ifdef USE_SERVO_CTRL
#include "Servo_Ctrl.h"
#endif

#ifdef USE_VOLTAGE
#include "Voltage.h"
#endif

#ifdef USE_LED_CTRL
#include "LED_Ctrl.h"
#endif

#ifdef USE_KEY_DETECT
#include "Key_Detect.h"
#endif

#ifdef USE_LINE_TRACKER
#include "LineTracker.h"
#endif

#ifdef USE_MOTOR_CTRL
#include "Motor_Ctrl.h"
#endif

#ifdef USE_IMU
#include "IMU.h"
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
    void led_set_brightness(const uint8_t& brightness);
    void led_set_blink_period(const int& period);
    void led_set_color(uint8_t led_id, const CRGB& color);
    void led_set_color(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b);
    void led_turn_on(uint8_t led_id);
    void led_turn_off(uint8_t led_id);
    void led_switch(uint8_t led_id);
    void led_blink(uint8_t led_id);
#endif

// Key Detection
#ifdef USE_KEY_DETECT
    void key_detect_update();
    void key_detect_get(uint8_t* key_data);
#endif

// Line Tracker
#ifdef USE_LINE_TRACKER
    void get_line_tracker(int* out, const char& dir);
#endif

// Motor Control
#ifdef USE_MOTOR_CTRL
    void move_motor(
        const char& side,
        const bool& rot_dir,
        const uint8_t& speed
    );
#endif

// IMU
#ifdef USE_IMU
    void imu_update();
    void imu_set_offsets(const std::array<int16_t, 6>& offsets);
    std::array<int16_t, 6> imu_get_offsets();
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

#ifdef USE_LINE_TRACKER
    LineTracker line_tracker_;
#endif

#ifdef USE_MOTOR_CTRL
    Motor_Ctrl motor_ctrl_;
#endif

#ifdef USE_IMU
    IMU* imu_;
#endif

};

#endif // SMART_CAR_H