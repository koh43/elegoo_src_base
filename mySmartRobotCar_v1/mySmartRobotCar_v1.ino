#include "ConstConfig.h"
#include "SmartCar.h"

SmartCar smart_car;

void setup() {
    Serial.begin(115200);
    smart_car.Init();
}

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
    smart_car.servo_update();
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
#endif

}

// Function to check if a string represents a number
bool isNumber(String& input) {
    for (unsigned int i = 0; i < input.length(); i++) {
        if (!isdigit(input.charAt(i))) {
            return false; // If a character is not a digit, it's not a number
        }
    }
    return true; // It's a number
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