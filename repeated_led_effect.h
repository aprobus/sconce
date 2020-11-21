#ifndef REPEATED_LED_EFFECT_H
#define REPEATED_LED_EFFECT_H

#include <memory>
#include <utility>
#include <limits>

#include "led_effect.h"

template <class T>
class RepeatedLedEffect : public LedEffect {
  public:
  template <class... Args>
  RepeatedLedEffect(Args&&... args) : effect_(std::forward<Args>(args)...) {}

  void update(unsigned long millis) {
    effect_.update(millis % effect_.length());
  }

  unsigned long length() const {
    return std::numeric_limits<unsigned long>::max();
  }

  private:
  T effect_;
};

class WrappedRepeatedLedEffect : public LedEffect {
  public:
  WrappedRepeatedLedEffect(std::unique_ptr<LedEffect> effect) : effect_(std::move(effect)) {}

  void update(unsigned long millis) {
    effect_->update(millis % effect_->length());
  }

  unsigned long length() const {
    return std::numeric_limits<unsigned long>::max();
  }
  private:
  std::unique_ptr<LedEffect> effect_;
};

#endif
