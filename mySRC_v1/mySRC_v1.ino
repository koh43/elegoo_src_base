#include <SoftwareSerial.h>
#include "SmartCar.h"

SmartCar smart_car;

// Connection with the ESP32 module
constexpr uint8_t UART_RX_PIN = 0;
constexpr uint8_t UART_TX_PIN = 1;
SoftwareSerial mySerial(UART_RX_PIN, UART_TX_PIN);

void setup() {
    Serial.begin(115200);
    mySerial.begin(115200);
    smart_car.Init();
#ifdef USE_LED_CTRL
    smart_car.led_set_color(0, CRGB::Red);
#endif
} // setup()

void loop() {
    String data_str;

    // Check if it is receiving remote serial input
    // if (mySerial.available()) {
    //     String received = mySerial.readStringUntil('\n');
    //     Serial.println(received);
    // }

// test servo motor
#ifdef USE_SERVO_CTRL
    if (mySerial.available()) {
        String received = mySerial.readStringUntil('\n');
        received.trim(); // Remove any trailing spaces or newline characters
        // Check if the input is a number
        if (isNumber(received)) {
            // Convert to integer and move the servo
            uint8_t angle = received.toInt();
            smart_car.servo_move_to(angle);
        } else {
            // If it's not a number, process as a sequence of commands
            for (unsigned int i = 0; i < received.length(); i++) {
                char command = received.charAt(i);
                servoCommand(smart_car, command);  // Process each command letter
            }
        }
    }
    smart_car.servo_update();
#endif

// test IMU (MPU6050)
#ifdef USE_IMU
    smart_car.imu_update(&data_str);
#endif
    
// test ultrasonic sensor
#ifdef USE_ULTRASONIC
    float us_dist;
    if (smart_car.get_us_dist(&us_dist)) {
        data_str += "us_dist:";
        data_str += String(us_dist/100) + "%";
    }
#endif
// test ir remote controller
#ifdef USE_IR_RM_CTRL
    char ir_rm_ctrl_data;
    if (smart_car.get_ctrl_input(&ir_rm_ctrl_data)) {
        Serial.print("IR Remote Input: ");
        Serial.print(ir_rm_ctrl_data);
        Serial.print(" \n");
    }

#endif

// test led control
#ifdef USE_LED_CTRL
    // smart_car.led_blink(0);
    smart_car.led_switch(0);
#endif

// test voltage sensor
#ifdef USE_VOLTAGE
    float volt_ms;
    smart_car.measure_voltage(&volt_ms);
    data_str += "voltage:";
    data_str += String(volt_ms) + "%";
#endif

// test key detect
#ifdef USE_KEY_DETECT
    smart_car.key_detect_update();
    uint8_t key_data;
    smart_car.key_detect_get(&key_data);
    Serial.print("Key Data:");
    Serial.print("\t");
    Serial.print(key_data);
    Serial.print("\n");
#endif

// test line tracker
#ifdef USE_LINE_TRACKER
    int lt_l;
    int lt_m;
    int lt_r;
    smart_car.get_line_tracker(&lt_l, 'L');
    smart_car.get_line_tracker(&lt_m, 'M');
    smart_car.get_line_tracker(&lt_r, 'R');
    data_str += "line_tracker:";
    data_str += String(lt_l) + ",";
    data_str += String(lt_m) + ",";
    data_str += String(lt_r) + "%";
#endif

// test motor control
#ifdef USE_MOTOR_CTRL
    smart_car.move_motor('l', true, 50);
    smart_car.move_motor('r', true, 50);
#endif

    Serial.println(data_str);

} // loop()

// Function to check if a string represents a number
#ifdef USE_SERVO_CTRL
bool isNumber(String& input) {
    for (unsigned int i = 0; i < input.length(); i++) {
        if (!isdigit(input.charAt(i))) {
            return false;
        }
    }
    return true;
}

void servoCommand(SmartCar& smart_car, char command) {
    switch (tolower(command)) {
        case 'a':
            smart_car.servo_turn_left();  // Assuming you have a TurnLeft method
            break;
        case 'd':
            smart_car.servo_turn_right(); // Assuming you have a TurnRight method
            break;
        case 'r':
            smart_car.servo_reset(); // Reset to initial position
            break;
        default:
            break;
    }
}
#endif