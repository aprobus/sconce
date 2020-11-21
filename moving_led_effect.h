#ifndef MOVING_LED_EFFECT_H
#define MOVING_LED_EFFECT_H

#include <stdint.h>

#include "led_effect.h"
#include "neopixel.h"

class MovingLedEffect : public LedEffect {
  public:
  MovingLedEffect(Neopixel* pixels, color_t color, unsigned long millis_per_pixel);
  void update(unsigned long millis) override;
  unsigned long length() const override;

  private:
  Neopixel* pixels_;
  color_t color_;
  unsigned long millis_per_pixel_;
};

#endif
