#ifndef MOVING_LED_EFFECT_H
#define MOVING_LED_EFFECT_H

#include <stdint.h>

#include "led_effect.h"
#include "led_strip.h"

class MovingLedEffect : public LedEffect {
  public:
  MovingLedEffect(LedStrip* pixels, color_t color, unsigned long millis_per_pixel);
  void update(unsigned long millis) override;
  unsigned long length() const override;

  private:
  LedStrip* pixels_;
  color_t color_;
  unsigned long millis_per_pixel_;
};

#endif
