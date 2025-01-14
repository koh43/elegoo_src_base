#include "SmartCar.h"

SmartCar smart_car;

void setup() {
    Serial.begin(115200);
    smart_car.Init();
#ifdef USE_LED_CTRL
    smart_car.led_set_color(0, CRGB::Red);
#endif
} // setup()

void loop() {
// test ultrasonic sensor
#ifdef USE_ULTRASONIC
    float us_dist;
    if (smart_car.get_us_dist(&us_dist)) {
        Serial.print("Distance: ");
        Serial.print(us_dist);
        Serial.print(" (cm)\n");
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
// test servo motor
#ifdef USE_SERVO_CTRL
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        input.trim(); // Remove any trailing spaces or newline characters
        // Check if the input is a number
        if (isNumber(input)) {
            // Convert to integer and move the servo
            uint8_t angle = input.toInt();
            Serial.print("Moving to angle: ");
            Serial.println(angle);
            smart_car.servo_move_to(angle);
        } else {
            // If it's not a number, process as a sequence of commands
            Serial.println("Executing letter commands...");
            for (unsigned int i = 0; i < input.length(); i++) {
                char command = input.charAt(i);
                servoCommand(smart_car, command);  // Process each command letter
            }
        }
    }
    smart_car.servo_update();
#endif

// test voltage sensor
#ifdef USE_VOLTAGE
    float volt_ms;
    smart_car.measure_voltage(&volt_ms);
    Serial.print("Voltage: ");
    Serial.print(volt_ms);
    Serial.print(" (V)\n");
#endif

// test led control
#ifdef USE_LED_CTRL
    smart_car.led_blink(0);
#endif

// test key detect
#ifdef USE_KEY_DETECT
    smart_car.key_detect_update();
    uint8_t key_data;
    smart_car.key_detect_get(&key_data);
    Serial.print("Key Data: ");
    Serial.print(key_data);
    Serial.print(" \n");
#endif

// test line tracker
#ifdef USE_LINE_TRACKER
    int lt_l;
    int lt_m;
    int lt_r;
    smart_car.get_line_tracker(&lt_l, 'L');
    smart_car.get_line_tracker(&lt_m, 'M');
    smart_car.get_line_tracker(&lt_r, 'R');
    Serial.print("Line Tracker (L, M, R): ");
    Serial.print(lt_l);
    Serial.print(", ");
    Serial.print(lt_m);
    Serial.print(", ");
    Serial.print(lt_r);
    Serial.print(" \n");
#endif

// test motor control
#ifdef USE_MOTOR_CTRL
    smart_car.move_motor('l', true, 100);
    smart_car.move_motor('r', true, 50);
#endif

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
    switch (command) {
        case 'A':
            Serial.println("Turning Left");
            smart_car.servo_turn_left();  // Assuming you have a TurnLeft method
            break;
        case 'D':
            Serial.println("Turning Right");
            smart_car.servo_turn_right(); // Assuming you have a TurnRight method
            break;
        case 'R':
            Serial.println("Resetting to initial angle");
            smart_car.servo_reset(); // Reset to initial position
            break;
        default:
            Serial.print("Unknown command: ");
            Serial.println(command);
            break;
    }
}
#endif