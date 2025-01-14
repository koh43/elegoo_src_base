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

#ifdef USE_VOLTAGE
    volt_.~Voltage();
#endif

#ifdef USE_LED_CTRL
    led_ctrl_.~LED_Ctrl();
#endif

#ifdef USE_KEY_DETECT
    key_detect_.~Key_Detect();
#endif

#ifdef USE_LINE_TRACKER
    line_tracker_.~LineTracker();
#endif

#ifdef USE_MOTOR_CTRL
    motor_ctrl_.~Motor_Ctrl();
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
    servo_ctrl_->Init();
#endif

#ifdef USE_VOLTAGE
    volt_.Init();
#endif

#ifdef USE_LED_CTRL
    led_ctrl_.Init();
#endif

#ifdef USE_KEY_DETECT
    key_detect_.Init();
#endif

#ifdef USE_LINE_TRACKER
    line_tracker_.Init();
#endif

#ifdef USE_MOTOR_CTRL
    motor_ctrl_.Init();
#endif

} // Init()

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
#ifdef USE_SERVO_CTRL
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
#endif

// Voltage Measurement
#ifdef USE_VOLTAGE
void SmartCar::measure_voltage(float* v_out) {
    volt_.GetVolt(v_out);
}
#endif

// LED Control
#ifdef USE_LED_CTRL
void SmartCar::led_set_brightness(uint8_t brightness) {
    led_ctrl_.SetBrightness(brightness);
}

void SmartCar::led_set_blink_period(int period) {
    led_ctrl_.SetBlinkPeriod(period);
}

void SmartCar::led_set_color(uint8_t led_id, CRGB color) {
    led_ctrl_.SetColor(led_id, color);
}

void SmartCar::led_set_color(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b) {
    led_ctrl_.SetColor(led_id, r, g, b);
}

void SmartCar::led_turn_on(uint8_t led_id) {
    led_ctrl_.TurnOn(led_id);
}

void SmartCar::led_turn_off(uint8_t led_id) {
    led_ctrl_.TurnOff(led_id);
}

void SmartCar::led_blink(uint8_t led_id) {
    led_ctrl_.Blink(led_id);
}
#endif

#ifdef USE_KEY_DETECT
void SmartCar::key_detect_update() {
    key_detect_.UpdateKeyInput();
}

void SmartCar::key_detect_get(uint8_t* key_data) {
    key_detect_.GetKeyInput(key_data);
}
#endif

#ifdef USE_LINE_TRACKER
void SmartCar::get_line_tracker(int* out, const char& dir) {
    line_tracker_.getAnalog(out, dir);
}
#endif

#ifdef USE_MOTOR_CTRL
void SmartCar::move_motor(
    const char& side,
    const bool& rot_dir,
    const uint8_t& speed
) {
    motor_ctrl_.Move(side, rot_dir, speed);
}
#endif
