#include "SerialHandler.h"
#include "CameraServer.h"
#include <WiFiUdp.h>

SerialHandler serial_handler;
CameraServer camera_server;


constexpr uint8_t UART_RX_PIN = 3;
constexpr uint8_t UART_TX_PIN = 40;
constexpr uint8_t STATUS_LED_PIN = 46;
constexpr int UDP_PORT = 9750;
bool led_flag = false;

WiFiUDP udp;

void setup() {
	Serial.begin(115200);
	Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
	camera_server.Init();
	udp.begin(UDP_PORT);
	pinMode(STATUS_LED_PIN, OUTPUT);
	digitalWrite(STATUS_LED_PIN, HIGH);
	// delay(100);
}

void loop() {
	serial_handler.receiveData(Serial1);
	// Check if it is receiving from the Arduino
	const uint8_t* last_data = serial_handler.getLastData();
	size_t last_data_size = serial_handler.getLastDataSize();
	if (last_data_size > 0) {
		udp.beginPacket("255.255.255.255", UDP_PORT);
		udp.write(last_data, last_data_size);
		udp.endPacket();
		delay(5);
	}
	
	if (led_flag) {
		digitalWrite(STATUS_LED_PIN, LOW);
		led_flag = false;
	}
	else {
		digitalWrite(STATUS_LED_PIN, HIGH);
		led_flag = true;
	}
}
