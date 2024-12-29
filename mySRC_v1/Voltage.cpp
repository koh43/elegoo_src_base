#include "Voltage.h"

Voltage::Voltage() {}

Voltage::~Voltage() {
    pinMode(VOLTAGE_PIN, INPUT);
}

void Voltage::Init() {
    pinMode(VOLTAGE_PIN, INPUT);
}

void Voltage::GetVolt(float* v_out) {
    *v_out = analogRead(VOLTAGE_PIN) * ADC_RESOLUTION * VOLT_DIV_CONST * VOLT_COMPENSATION;
}