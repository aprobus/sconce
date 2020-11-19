#ifndef PULSE_LED_EFFECT_H
#define PULSE_LED_EFFECT_H

#include "led_effect.h"
#include "neopixel.h"

class PulseLedEffect : public TimedLedEffect {
  public:
    PulseLedEffect(Neopixel* pixels, color_t color, unsigned long pulse_millis);
    void update(unsigned long millis) override;
    unsigned long length() const override;
  private:
    Neopixel* pixels_;
    color_t color_;
    unsigned long pulse_millis_;
};

#endif