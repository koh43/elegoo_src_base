#include "LED_ctrl.h"

LED_Ctrl::LED_Ctrl() {}

LED_Ctrl::~LED_Ctrl() {
    FastLED.clear();
}

void LED_Ctrl::Init() {
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds_, NUM_LEDS);
    SetBrightness(INIT_LED_BRIGHTNESS);
    SetBlinkPeriod(INIT_LED_BLINK_PERIOD);
    is_on_ = false;
    last_time_ = millis();
    current_time_ = last_time_;
    time_elapsed_ = 0;
}

void LED_Ctrl::SetBrightness(uint8_t brightness) {
    brightness_ = brightness;
    // FastLED.setBrightness(brightness_);
}

void LED_Ctrl::SetBlinkPeriod(int period) {
    period_ = period;
}

void LED_Ctrl::SetColor(uint8_t led_id, CRGB color) {
    Serial.println("Setting color");
    if (led_id < NUM_LEDS) {
        colors_[led_id] = color;
    }
}

void LED_Ctrl::SetColor(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b) {
    if (led_id < NUM_LEDS) {
        colors_[led_id] = CRGB(r, g, b);
    }
}

void LED_Ctrl::TurnOn(uint8_t led_id) {
    is_on_ = true;
    if (led_id < NUM_LEDS) {
        leds_[led_id] = colors_[led_id];
        FastLED.setBrightness(brightness_);
        FastLED.show();
        Serial.println("Turning on LED");
    }
}

void LED_Ctrl::TurnOff(uint8_t led_id) {
    is_on_ = false;
    if (led_id < NUM_LEDS) {
        FastLED.clear();
        FastLED.setBrightness(brightness_);
        FastLED.show();
        Serial.println("Turning off LED");
    }
}

void LED_Ctrl::Blink(uint8_t led_id) {
    current_time_ = millis();
    time_elapsed_ = current_time_ - last_time_;
    if (time_elapsed_ >= period_) {
        if (is_on_) {
            TurnOff(led_id);
        }
        else {
            TurnOn(led_id);
        }
        last_time_ = current_time_;
    }
}