#include "interleaved_led_effect.h"

#include <limits>

#include "neopixel.h"
#include "color_function.h"

InterleavedLedEffect::InterleavedLedEffect(Neopixel* pixels) : pixels_(pixels) {}

void InterleavedLedEffect::update(unsigned long millis) {
  for (int i = 0; i < colors_functions_.size(); i++) {
    const auto& color_f = colors_functions_[i];
    color_t c = color_f->color(millis % color_f->length());
    for (int j = i; j < pixels_->numPixels(); j += colors_functions_.size()) {
      pixels_->setPixelColor(j, c);
    }
  }

  pixels_->show();
}

unsigned long InterleavedLedEffect::length() const {
  return std::numeric_limits<unsigned long>::max();
}

void InterleavedLedEffect::pushBack(std::unique_ptr<ColorFunction> f) {
  colors_functions_.push_back(std::move(f));
}
