#ifndef REPEATED_LED_EFFECT_H
#define REPEATED_LED_EFFECT_H

#include <memory>
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

class WrappedRepeatedLedEffect : public LedEffect {
  public:
  WrappedRepeatedLedEffect(std::unique_ptr<TimedLedEffect> effect) : effect_(std::move(effect)) {}

  void update(unsigned long millis) {
    effect_->update(millis % effect_->length());
  }
  private:
  std::unique_ptr<TimedLedEffect> effect_;
};

#endif