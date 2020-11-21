#ifndef MOCK_LED_EFFECT_H
#define MOCK_LED_EFFECT_H

#include "led_effect.h"

class MockEffect : public LedEffect {
  public:
  MockEffect(unsigned long* millis) : last_millis_(millis) {}

  void update(unsigned long millis) override {
    *last_millis_ = millis;
  }

  unsigned long length() const override {
    return 100;
  }

  unsigned long* last_millis_;
};
#endif
