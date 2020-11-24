#ifndef INTERLEAVED_LED_EFFECT_H
#define INTERLEAVED_LED_EFFECT_H

#include <memory>
#include <utility>
#include <vector>

#include "led_effect.h"
#include "neopixel.h"
#include "color_function.h"

class InterleavedLedEffect : public LedEffect {
  public:
    InterleavedLedEffect(Neopixel* pixels);
    void update(unsigned long millis) override;
    unsigned long length() const override;
    void pushBack(std::unique_ptr<ColorFunction> f);

    template <class T, class... Args>
    void emplaceBack(Args&&... args) {
      pushBack(std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
    }
  private:
    Neopixel* pixels_;
    std::vector<std::unique_ptr<ColorFunction>> colors_functions_;
};

#endif
