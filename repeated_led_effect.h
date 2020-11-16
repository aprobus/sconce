#ifndef REPEATED_LED_EFFECT_H
#define REPEATED_LED_EFFECT_H

#include <utility>

#include "led_effect.h"

template <class T>
class RepeatedLedEffect : public LedEffect {
  public:
  template <class... Args>
  RepeatedLedEffect(Args&&... args) : effect_(std::forward<Args>(args)...) {}

  void update(unsigned long millis) {
    effect_.update(millis % effect_.length());
  }
  private:
  T effect_;
};

#endif