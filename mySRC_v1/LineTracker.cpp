#include "LineTracker.h"

LineTracker::LineTracker() {}

LineTracker::~LineTracker() {
    pinMode(LINE_TRACKER_PIN_R, INPUT);
    pinMode(LINE_TRACKER_PIN_M, INPUT);
    pinMode(LINE_TRACKER_PIN_L, INPUT);
}

void LineTracker::Init() {
    pinMode(LINE_TRACKER_PIN_R, INPUT);
    pinMode(LINE_TRACKER_PIN_M, INPUT);
    pinMode(LINE_TRACKER_PIN_L, INPUT);
}

/*
- Low Values (close to 0)
: High reflectivity. Surface reflects the IR light back to the sensor at a 
high rate, corresponding to a white or light-colored surface.

- High Values (close to 1023 for 10-bit ADC)
: Low reflectivity. Surface absorbs more IR light and reflects less.
Corresponds to a black or dark-colored surface.
*/
void LineTracker::getAnalog(int* out, const char& dir) {
    if (tolower(dir) == 'r') {
        *out = analogRead(LINE_TRACKER_PIN_R);
    }
    else if (tolower(dir) == 'm') {
        *out = analogRead(LINE_TRACKER_PIN_M);
    }
    else if (tolower(dir) == 'l') {
        *out = analogRead(LINE_TRACKER_PIN_R);
    }
    else {
        Serial.println("Line Tracker has L, M, and R sensors...");
        *out = 0;
    }
}