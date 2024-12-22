#ifndef LED_CTRL_H
#define LED_CTRL_H

#include <FastLED.h>
#include <Arduino.h>

constexpr uint8_t NUM_LEDS = 1;
constexpr uint8_t LED_PIN  = 4;
constexpr uint8_t INIT_LED_BRIGHTNESS = 5;
constexpr int INIT_LED_BLINK_PERIOD = 1000;

class LED_Ctrl {
public:
    LED_Ctrl();
    ~LED_Ctrl();
    void Init();
    void SetBrightness(uint8_t brightness);
    void SetBlinkPeriod(int period);
    void SetColor(uint8_t led_id, CRGB& color);
    void SetColor(uint8_t led_id, uint8_t r, uint8_t g, uint8_t b);
    void TurnOn(uint8_t led_id);
    void TurnOff(uint8_t led_id);
    void Blink(uint8_t led_id);
private:
    CRGB leds_[NUM_LEDS];
    CRGB colors_[NUM_LEDS];
    bool is_on_;
    unsigned long current_time_;
    unsigned long last_time_;
    unsigned long time_elapsed_;
    int period_;
    uint8_t brightness_;
};

#endif // LED_CTRL_H