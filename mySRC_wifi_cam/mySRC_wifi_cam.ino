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

constexpr size_t CMD_BUFFER_SIZE = 64;
char cmd_buffer[CMD_BUFFER_SIZE];

WiFiUDP udp;

void setup() {
	Serial.begin(115200);
	Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
	camera_server.Init();
	udp.begin(UDP_PORT);
	pinMode(STATUS_LED_PIN, OUTPUT);
	digitalWrite(STATUS_LED_PIN, HIGH);
	delay(10);
}

void loop() {
	serial_handler.receiveData(Serial1);

	// Check if it is receiving from the Arduino
	const char* last_data = serial_handler.getLastData();
	Serial.print(last_data);
	size_t last_data_size = serial_handler.getLastDataSize();
	if (last_data_size > 0) {
		udp.beginPacket("255.255.255.255", UDP_PORT);
		udp.write(
			reinterpret_cast<const uint8_t*>(last_data),
			last_data_size
		);
		udp.endPacket();
		delay(5);
	}

	digitalWrite(STATUS_LED_PIN, led_flag ? LOW : HIGH);
	led_flag = !led_flag;

	int packet_size = udp.parsePacket();
	if (packet_size > 0) {
		int len = udp.read(cmd_buffer, CMD_BUFFER_SIZE - 1);
		cmd_buffer[len] = '\0';
		Serial1.write(cmd_buffer, strlen(cmd_buffer));
		Serial.print("Sent to Arduino: ");
		Serial.println(cmd_buffer);
		delay(5);
	}
}
