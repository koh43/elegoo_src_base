#include "Voltage.h"

Voltage::Voltage(uint8_t voltage_pin) : voltage_pin_(voltage_pin) {}

Voltage::~Voltage() {
    pinMode(voltage_pin_, INPUT);
}

void Voltage::Init() {
    pinMode(voltage_pin_, INPUT);
}

void Voltage::GetVolt(float* volt) {
    *volt = analogRead(voltage_pin_) * ADC_RESOLUTION * VOLT_DIV_CONST * VOLT_COMPENSATION;
}