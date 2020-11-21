#ifndef SOLID_LED_EFFECT_H
#define SOLID_LED_EFFECT_H

#include "led_effect.h"
#include "neopixel.h"

class SolidLedEffect : public LedEffect {
  public:
  SolidLedEffect(Neopixel* pixels, color_t color);
  ~SolidLedEffect() = default;
  void update(unsigned long millis) override;
  unsigned long length() const override;
  private:
    Neopixel* pixels_;
    color_t color_;
};
#endif
