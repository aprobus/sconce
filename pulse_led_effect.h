#ifndef PULSE_LED_EFFECT_H
#define PULSE_LED_EFFECT_H

#include "led_effect.h"
#include "neopixel.h"

class PulseLedEffect : public LedEffect {
  public:
    PulseLedEffect(Neopixel* pixels, color_t color, unsigned long pulse_millis);
    void begin() override;
    void update(unsigned long millis) override;
  private:
    Neopixel* pixels_;
    color_t color_;
    unsigned long pulse_millis_;
};

#endif
