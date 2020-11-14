#ifndef LED_EFFECT_DRIVER_H
#define LED_EFFECT_DRIVER_H

#include <vector>
#include <memory>

#include "led_effect.h"

class LedEffectDriver {
  public:
    void begin();
    void next(unsigned long millis);
    void onTimerUpdated(unsigned long millis);

    void pushBack(std::unique_ptr<LedEffect> effect);

    template <class T, class... Args> void emplaceBack(Args&&... args) {
      led_effects_.emplace_back(new T(std::forward<Args>(args)...));
    }
  private:
    std::vector<std::unique_ptr<LedEffect>> led_effects_;
    unsigned long switched_at_millis_ = 0;
    int index_ = 0;
};

#endif
