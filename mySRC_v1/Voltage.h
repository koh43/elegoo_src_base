#ifndef VOLTAGE_H
#define VOLTAGE_H

#include <Arduino.h>

constexpr uint8_t VOLTAGE_PIN = A3;
/*
Arduino ADCs are 10bits in general
Analog sensor values are btw 0 to 1023
Digital Voltage Values are btw 0-5V
*/
constexpr float ADC_RESOLUTION = 5 / 1023;
/*
When you want to measure voltages above 5V, voltage dividers are used to map
the voltage going into the board (board cannot accept voltages over 5V).
Va = Vm * (R2/(R1+R2))
where Va will be the voltage going in to the Arduino and Vm is the raw voltage
you want to measure.
Hence, to measure the raw voltage,
Vm = Va * ((R1+R2)/R2)
The resistor values used in this circuit are
R1 = 10 Ohm, R2 = 1.5 Ohm
*/
constexpr float VOLT_DIV_CONST = (10 + 1.5) / 1.5;
constexpr float VOLT_COMPENSATION = 1.08; // 8% Compensation

class Voltage {
public:
    Voltage();
    ~Voltage();
    void Init();
    void GetVolt(float* v_out);
};

#endif // VOLTAGE_H