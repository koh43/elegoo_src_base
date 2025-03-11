#include <SoftwareSerial.h>
#include "SmartCar.h"

SmartCar smart_car;

// Connection with the ESP32 module
constexpr uint8_t UART_RX_PIN = 0;
constexpr uint8_t UART_TX_PIN = 1;
SoftwareSerial mySerial(UART_RX_PIN, UART_TX_PIN);

// Buffers
constexpr size_t CMD_BUFFER_SIZE = 64;
constexpr size_t DATA_BUFFER_SIZE = 128;
char cmd_buffer[CMD_BUFFER_SIZE];
char data_buffer[DATA_BUFFER_SIZE];

void setup() {
    Serial.begin(115200);
    mySerial.begin(115200);
    smart_car.Init();
#ifdef USE_LED_CTRL
    smart_car.led_set_color(0, CRGB::Red);
#endif
} // setup()

void loop() {
    processCommands();
    processSensors();
} // loop()

// ===========================
// Command Processing
// ===========================
void processCommands() {
    if (!mySerial.available()) return;

    int cmd_len = mySerial.readBytesUntil('\n', cmd_buffer, sizeof(cmd_buffer) - 1);
    cmd_buffer[cmd_len] = '\0'; // Add null terminator

    Serial.print("Received: ");
    Serial.println(cmd_buffer);

    char* sep_ptr = strchr(cmd_buffer, ':');
    if (!sep_ptr) return;
    *sep_ptr = '\0';

    const char* cmd_device = cmd_buffer;
    const char* cmd_value = sep_ptr + 1;

// servo control
#ifdef USE_SERVO_CTRL
    if (strcmp(cmd_device, "servo") == 0) {
        Serial.println("Moving Servo...");
        processServo(cmd_value);
    }
    smart_car.servo_update();
#endif

// motor control
#ifdef USE_MOTOR_CTRL
    if (strcmp(cmd_device, "motor") == 0) {
        Serial.println("Moving motor...");
        processMotor(cmd_value);
    }
#endif
}

// ===========================
// Servo Processing
// ===========================
#ifdef USE_SERVO_CTRL
void processServo(const char* cmd_value) {
    // Check if the input is a number
    if (isNumber(cmd_value)) {
        // Convert to integer and move the servo
        uint8_t angle = atoi(cmd_value);
        smart_car.servo_move_to(angle);
    } else {
        // If it's not a number, process as a sequence of commands
        for (unsigned int i = 0; i < strlen(cmd_value); i++) {
            servoCommand(smart_car, cmd_value[i]);  // Process each command letter
        }
    }
}

bool isNumber(const char* input) {
    for (unsigned int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

void servoCommand(SmartCar& smart_car, char command) {
    switch (tolower(command)) {
        case 'a': smart_car.servo_turn_left(); break;
        case 'd': smart_car.servo_turn_right(); break;
        case 'r': smart_car.servo_reset(); break;
        default: break;
    }
}
#endif

// ===========================
// Motor Processing
// ===========================
#ifdef USE_MOTOR_CTRL
void processMotor(const char* cmd_value) {
    char side;
    int rot_dir, speed;
    if (sscanf(cmd_value, "%c,%d,%d", &side, &rot_dir, &speed) == 3) {
        bool rot_dir_bool = (rot_dir == 1); // Convert -1/1 to boolean
        smart_car.move_motor(side, rot_dir, speed);
    }
    else {
        Serial.println("Invalid motor command format.");
    }
}
#endif

// ===========================
// Sensor Processing
// ===========================
void processSensors() {
    int index = 0;

// test IMU (MPU6050)
#ifdef USE_IMU
char imu_data[48];
    smart_car.imu_update(imu_data);
    index += snprintf(
        data_buffer + index,
        DATA_BUFFER_SIZE - index,
        "%s", imu_data
    );
#endif
    
// test ultrasonic sensor
#ifdef USE_ULTRASONIC
    float us_dist;
    if (smart_car.get_us_dist(&us_dist)) {
        char buffer[16];
        dtostrf(us_dist, 6, 4, buffer);
        index += snprintf(
            data_buffer + index,
            DATA_BUFFER_SIZE - index,
            "us_dist:%s%%",
            buffer
        );
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
    smart_car.led_switch(0);
#endif

// test voltage sensor
#ifdef USE_VOLTAGE
    float volt_ms;
    smart_car.measure_voltage(&volt_ms);
    if (volt_ms >= 0){
        char buffer[16];
        dtostrf(volt_ms, 3, 2, buffer);
        index += snprintf(
            data_buffer + index,
            DATA_BUFFER_SIZE - index,
            "voltage:%s%%",
            buffer
        );
    }
    
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
    index += snprintf(
        data_buffer + index,
        DATA_BUFFER_SIZE - index,
        "line_tracker:%d,%d,%d%%",
        lt_l, lt_m, lt_r
    );
#endif
    data_buffer[index] = '\n';
    data_buffer[index + 1] = '\0';
    Serial.write(data_buffer, strlen(data_buffer));
    // Serial.println(data_buffer);
}