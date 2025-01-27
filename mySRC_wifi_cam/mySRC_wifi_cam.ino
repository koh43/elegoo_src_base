#include "SerialHandler.h"
#include "CameraServer.h"

SerialHandler serial_handler;
CameraServer camera_server;

constexpr uint8_t UART_RX_PIN = 3;
constexpr uint8_t UART_TX_PIN = 40;
constexpr uint8_t STATUS_LED_PIN = 46;
bool led_flag = false;

void setup() {
	Serial.begin(115200);
	Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
	camera_server.Init();
	pinMode(STATUS_LED_PIN, OUTPUT);
	digitalWrite(STATUS_LED_PIN, HIGH);
	delay(100);
}

void loop() {
	serial_handler.receiveData(Serial1);
	String last_data;
	last_data = serial_handler.getLastData();
	Serial.println(last_data);
	if (led_flag) {
		digitalWrite(STATUS_LED_PIN, LOW);
		led_flag = false;
		delay(10);
	}
	else {
		digitalWrite(STATUS_LED_PIN, HIGH);
		led_flag = true;
	}
}
