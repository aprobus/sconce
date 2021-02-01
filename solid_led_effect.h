#ifndef SOLID_LED_EFFECT_H
#define SOLID_LED_EFFECT_H

#include "led_effect.h"
#include "led_strip.h"

class SolidLedEffect : public LedEffect {
  public:
  SolidLedEffect(LedStrip* pixels, color_t color);
  ~SolidLedEffect() = default;
  void update(unsigned long millis) override;
  unsigned long length() const override;
  private:
    LedStrip* pixels_;
    color_t color_;
};
#endif
