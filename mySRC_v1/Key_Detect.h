#ifndef KEY_DETECT_H
#define KEY_DETECT_H

#include <Arduino.h>

constexpr uint8_t KEY_PIN = 2;
constexpr uint8_t MAX_KEY_VALUE = 4;
constexpr int KEY_DEBOUNCE_TIME = 200;

class Key_Detect {
public:
    Key_Detect();
    ~Key_Detect();
    void Init();
    void UpdateKeyInput();
    void GetKeyInput(uint8_t* key_data);

private:
    uint8_t key_val_;
    bool is_falling_;
    unsigned long last_fall_t_;
};

#endif // KEY_DETECT_H