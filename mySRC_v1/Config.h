#ifndef CONFIG_H
#define CONFIG_H

/*
Comment or uncomment based on the codes you want to run!
*/

// #define USE_IR_RM_CTRL

#define USE_MOTOR_CTRL
#define USE_ULTRASONIC
#define USE_VOLTAGE
#define USE_LINE_TRACKER
// #define USE_KEY_DETECT
#define USE_LED_CTRL
#define USE_SERVO_CTRL
#define USE_IMU

#ifdef USE_IMU
  #define IMU_DATA_BUFFER_SIZE 48
#else
  #define IMU_DATA_BUFFER_SIZE 0
#endif

#ifdef USE_ULTRASONIC
  #define US_DATA_BUFFER_SIZE 12
#else
  #define US_DATA_BUFFER_SIZE 0
#endif

#ifdef USE_VOLTAGE
  #define VOLTAGE_DATA_BUFFER_SIZE 8
#else
  #define VOLTAGE_DATA_BUFFER_SIZE 0
#endif

#ifdef USE_LINE_TRACKER
  #define LINE_TRACKER_DATA_BUFFER_SIZE 16
#else
  #define LINE_TRACKER_DATA_BUFFER_SIZE 0
#endif

#define MAX_SENSOR_DATA_BUFFER_SIZE \
  (IMU_DATA_BUFFER_SIZE + US_DATA_BUFFER_SIZE + VOLTAGE_DATA_BUFFER_SIZE + LINE_TRACKER_DATA_BUFFER_SIZE)

#endif // CONFIG_H