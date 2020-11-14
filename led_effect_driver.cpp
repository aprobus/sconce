#include "led_effect_driver.h"

#include <memory>

#include "led_effect.h"

void LedEffectDriver::begin() {
  if (led_effects_.empty()) {
    return;
  }

  led_effects_[index_]->begin();
}

void LedEffectDriver::next(unsigned long millis) {
  if (led_effects_.empty()) {
    return;
  }

  switched_at_millis_ = millis;
  index_ = (index_ + 1) % led_effects_.size();
  led_effects_[index_]->begin();
}

void LedEffectDriver::onTimerUpdated(unsigned long millis) {
  if (led_effects_.empty()) {
    return;
  }

  led_effects_[index_]->update(millis - switched_at_millis_);
}

void LedEffectDriver::pushBack(std::unique_ptr<LedEffect> effect) {
  led_effects_.push_back(std::move(effect));
}
