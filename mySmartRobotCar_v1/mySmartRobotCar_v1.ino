#include <Arduino.h>
#include <avr/wdt.h>
#include "SmartCar.h"

SmartCar scar;

void setup() {
    Serial.begin(9600);
    scar.SmartCarInit();
}

void loop() {
    float us_dist = scar.get_us_dist();
    Serial.print("Distance: ");
    Serial.print(us_dist);
    Serial.print(" (cm)\n");
    delay(500);
}