#ifndef SEQUENTIAL_LED_EFFECT_H
#define SEQUENTIAL_LED_EFFECT_H

#include <memory>
#include <vector>
#include <utility>

#include "led_effect.h"

class SequentialLedEffect : public LedEffect {
  public:
  SequentialLedEffect() = default;
  void update(unsigned long millis) override;
  unsigned long length() const override;

  template <class T, class... Args>
  void emplaceBack(Args&&... args) {
    pushBack(std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
  }

  void pushBack(std::unique_ptr<LedEffect> effect);

  private:
  struct EffectInterval {
    unsigned long start = 0;
    unsigned long end = 0;
    std::unique_ptr<LedEffect> effect;
  };
  std::vector<EffectInterval> effects_;
};

#endif
