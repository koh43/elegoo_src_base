#include "./Key_Detect.h"

Key_Detect::Key_Detect() {}

Key_Detect::~Key_Detect() {
    pinMode(KEY_PIN, INPUT);
}

void Key_Detect::Init() {
    pinMode(KEY_PIN, INPUT_PULLUP);
    is_falling_ = false;
    key_val_ = 0;
    last_fall_t_ = 0;
}

void Key_Detect::UpdateKeyInput() {
    unsigned long current_t = millis();
    unsigned long elapsed_t = current_t - last_fall_t_;
    if (digitalRead(KEY_PIN) == LOW) {
        if(is_falling_) {
            if (elapsed_t > KEY_DEBOUNCE_TIME) {
                key_val_++;
                last_fall_t_ = current_t;
                if (key_val_ > MAX_KEY_VALUE) {
                    key_val_ = 0;
                }
            }
            is_falling_ = false;
        }
    }
    else {
        is_falling_ = true;
    }
}

void Key_Detect::GetKeyInput(uint8_t* key_data) {
    *key_data = key_val_;
}