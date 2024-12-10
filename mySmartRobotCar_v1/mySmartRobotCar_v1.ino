#include <avr/wdt.h>
#include <IRremote.h>
#include <Servo.h>
#include "SmartCar.h"
#include "ConstConfig.h"

/*
For some reason, the IR remote controller works properlly
only when the object is defined globally (no idea why :/).
Otherwise, you might get different raw values when pressing the
same button.
Please use IRremote versions 2.x.x or lower
*/
#ifdef USE_IR_RM_CTRL
IRrecv irrecv(IR_RECEIVER_PIN); //  Create an infrared receive drive object
decode_results results;
#endif

#ifdef USE_SERVO_CTRL
Servo servo;
#endif

#ifdef RUN_SMART_CAR
SmartCar smart_car(
    servo
);

void setup() {
    Serial.begin(115200);
#ifdef USE_IR_RM_CTRL
    irrecv.enableIRIn();
#endif
    // wdt_enable(WDTO_2S);
}

void loop() {
    // Sensor motion timing updates
    smart_car.servo_update();
    // test ultrasonic sensor
    float us_dist;
    if (smart_car.get_us_dist(&us_dist)) {
        Serial.print("Distance: ");
        Serial.print(us_dist);
        Serial.print(" (cm)\n");
    }
    // test ir remote controller
#ifdef USE_IR_RM_CTRL
    uint8_t ir_rm_ctrl_data;
    if(smart_car.get_ir_rm_ctrl_input(irrecv, results, &ir_rm_ctrl_data)) {
        Serial.print("IR Remote Input: ");
        Serial.print(ir_rm_ctrl_data);
        Serial.print(" \n");
    }
#endif
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
                servoCommand(command);  // Process each command letter
            }
        }
    }
    delay(500);
}
#endif

// Function to check if a string represents a number
bool isNumber(String input) {
    for (unsigned int i = 0; i < input.length(); i++) {
        if (!isdigit(input.charAt(i))) {
            return false; // If a character is not a digit, it's not a number
        }
    }
    return true; // It's a number
}

// Function to handle letter servo commands
void servoCommand(char command) {
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