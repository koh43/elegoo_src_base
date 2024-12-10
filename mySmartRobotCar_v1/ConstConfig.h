#ifndef CONST_CONFIG_H
#define CONST_CONFIG_H

/*
Comment or uncomment based on the codes you want to run!
*/
#define RUN_SMART_CAR
// #define USE_IR_RM_CTRL
#define USE_SERVO_CTRL

// Choose your remote controller type
#define IR_RM_CTRL_A
// #define IR_RM_CTRL_B

#include <avr/wdt.h>
static void
delay_xxx(uint16_t _ms)
{
  wdt_reset();
  for (unsigned long i = 0; i < _ms; i++)
  {
    delay(1);
  }
}

// Ultrasonic
constexpr float   ULTRASONIC_SENSOR_SPEED = 0.0343; // (cm / microsec)
constexpr uint8_t ULTRASONIC_TRIG_PIN = 13;
constexpr uint8_t ULTRASONIC_ECHO_PIN = 12;
constexpr float   ULTRASONIC_MAX_DIST = 400.0; // (cm)

// IR remote controller
constexpr uint8_t IR_RECEIVER_PIN = 9;

// Uncomment or comment based on your remote controller type :)
#ifdef IR_RM_CTRL_A
constexpr unsigned long RECV_up    = 16736925;
constexpr unsigned long RECV_down  = 16754775;
constexpr unsigned long RECV_left  = 16720605;
constexpr unsigned long RECV_right = 16761405;
constexpr unsigned long RECV_ok    = 16712445;
constexpr unsigned long RECV_1     = 16738455;
constexpr unsigned long RECV_2     = 16750695;
constexpr unsigned long RECV_3     = 16756815;
constexpr unsigned long RECV_4     = 16724175;
constexpr unsigned long RECV_5     = 16718055;
constexpr unsigned long RECV_6     = 16743045;
constexpr unsigned long RECV_7     = 16716015;
constexpr unsigned long RECV_8     = 16726215;
constexpr unsigned long RECV_9     = 16734885;
constexpr unsigned long RECV_0     = 16730805;
constexpr unsigned long RECV_star  = 16728765;
constexpr unsigned long RECV_sharp = 16732845;
#endif

#ifdef IR_RM_CTRL_B
constexpr unsigned long RECV_up    = 5316027   ;
constexpr unsigned long RECV_down  = 2747854299;
constexpr unsigned long RECV_left  = 1386468383;
constexpr unsigned long RECV_right = 553536955 ;
constexpr unsigned long RECV_ok    = 3622325019;
constexpr unsigned long RECV_1     = 3238126971;
constexpr unsigned long RECV_2     = 2538093563;
constexpr unsigned long RECV_3     = 4039382595;
constexpr unsigned long RECV_4     = 2534850111;
constexpr unsigned long RECV_5     = 1033561079;
constexpr unsigned long RECV_6     = 1635910171;
constexpr unsigned long RECV_7     = 2351064443;
constexpr unsigned long RECV_8     = 1217346747;
constexpr unsigned long RECV_9     = 71952287  ;
#endif

// Servo Pin
constexpr uint8_t SERVO_PIN = 10;
constexpr unsigned int SERVO_DEGREE_ZERO_POS = 500;
constexpr unsigned int SERVO_DEGREE_PI_POS = 2400;
constexpr uint8_t SERVO_INIT_ANGLE = 90;
constexpr uint8_t SERVO_MIN_DEGREE = 0;
constexpr uint8_t SERVO_MAX_DEGREE = 180;
constexpr float SERVO_SPEED = 90 / 500; // 90 degrees per 500ms

#endif // CONST_CONFIG_H