#ifndef PULSE_LED_EFFECT_H
#define PULSE_LED_EFFECT_H

#include "led_effect.h"
#include "neopixel.h"
#include "pulse_color_function.h"

class PulseLedEffect : public LedEffect {
  public:
    PulseLedEffect(Neopixel* pixels, PulseColorFunction f);
    void update(unsigned long millis) override;
    unsigned long length() const override;
  private:
    Neopixel* pixels_;
    PulseColorFunction pulse_function_;
};

#endif
