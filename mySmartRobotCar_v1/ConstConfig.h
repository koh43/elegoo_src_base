#ifndef CONST_CONFIG_H
#define CONST_CONFIG_H

/*
Comment or uncomment based on the codes you want to run!
*/
#define USE_ULTRASONIC
// #define USE_IR_RM_CTRL
#define USE_SERVO_CTRL
#define USE_VOLTAGE

// Ultrasonic
#ifdef USE_ULTRASONIC
constexpr float   ULTRASONIC_SENSOR_SPEED = 0.0343; // (cm / microsec)
constexpr uint8_t ULTRASONIC_TRIG_PIN = 13;
constexpr uint8_t ULTRASONIC_ECHO_PIN = 12;
constexpr float   ULTRASONIC_MAX_DIST = 400.0; // (cm)
#endif

// IR remote controller
#ifdef USE_IR_RM_CTRL
// IR remote controller
constexpr uint8_t IR_RECEIVER_PIN = 9;
// Choose your remote controller type
#define IR_RM_CTRL_A
// #define IR_RM_CTRL_B

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
#endif

// Servo Control
#ifdef USE_SERVO_CTRL
constexpr uint8_t SERVO_PIN = 10;
constexpr unsigned int SERVO_DEGREE_ZERO_POS = 500;
constexpr unsigned int SERVO_DEGREE_PI_POS = 2400;
constexpr uint8_t SERVO_INIT_ANGLE = 90;
constexpr uint8_t SERVO_MIN_DEGREE = 0;
constexpr uint8_t SERVO_MAX_DEGREE = 180;
constexpr float SERVO_SPEED = 90 / 500; // 90 degrees per 500ms
#endif

// Voltage Control
#ifdef USE_VOLTAGE
constexpr uint8_t VOLTAGE_PIN = A3;
/*
Arduino ADCs are 10bits in general
Analog sensor values are btw 0 to 1023
Digital Voltage Values are btw 0-5V
*/
constexpr float ADC_RESOLUTION = 5 / 1023;
/*
When you want to measure voltages above 5V, voltage dividers are used to map
the voltage going into the board (board cannot accept voltages over 5V).
Va = Vm * (R2/(R1+R2))
where Va will be the voltage going in to the Arduino and Vm is the raw voltage
you want to measure.
Hence, to measure the raw voltage,
Vm = Va * ((R1+R2)/R2)
The resistor values used in this circuit are
R1 = 10 Ohm, R2 = 1.5 Ohm
*/
constexpr float VOLT_DIV_CONST = (10 + 1.5) / 1.5;
constexpr float VOLT_COMPENSATION = 1.08; // 8% Compensation
#endif

#endif // CONST_CONFIG_H