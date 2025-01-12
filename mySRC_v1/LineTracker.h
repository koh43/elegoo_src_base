#ifndef LINE_TRACKER_H
#define LINE_TRACKER_H

#include <Arduino.h>

constexpr uint8_t LINE_TRACKER_PIN_R = A0;
constexpr uint8_t LINE_TRACKER_PIN_M = A1;
constexpr uint8_t LINE_TRACKER_PIN_L = A2;

class LineTracker {
public:
    LineTracker();
    ~LineTracker();
    void Init();
    void getAnalog(int* out, const char& dir);
};

#endif // LINE_TRACKER_H