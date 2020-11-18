#include "sequential_led_effect.h"

unsigned long SequentialLedEffect::length() const {
  if (effects_.empty()) {
    return 0;
  } else {
    return effects_.back().end;
  }
}

void SequentialLedEffect::update(unsigned long millis) {
  if (effects_.empty() || millis >= effects_.back().end) {
    return;
  }

  int left = 0;
  int right = effects_.size() - 1;
  while (right > left) {
    int mid = left + (right - left) / 2;

    if (effects_[mid].end <= millis) {
      left = mid + 1;
    } else if (millis < effects_[mid].start) {
      right = mid - 1;
    } else {
      break;
    }
  }

  const auto& x = effects_[left];
  x.effect->update(millis - x.start);
}

void SequentialLedEffect::pushBack(std::unique_ptr<TimedLedEffect> effect) {
    EffectInterval interval;
    interval.effect = std::move(effect);
    if (effects_.empty()) {
      interval.start = 0;
    } else {
      interval.start = effects_.back().end;
    }
    interval.end = interval.start + interval.effect->length();

    effects_.push_back(std::move(interval));
}