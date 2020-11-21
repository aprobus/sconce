#include "interleaved_led_effect.h"

#include "neopixel.h"
#include "color_function.h"

InterleavedLedEffect::InterleavedLedEffect(Neopixel* pixels) : pixels_(pixels) {}

void InterleavedLedEffect::update(unsigned long millis) {
  if (millis >= length_) {
    return;
  }

  for (int i = 0; i < colors_functions_.size(); i++) {
    color_t c = colors_functions_[i]->color(millis);
    for (int j = i; j < pixels_->numPixels(); j += colors_functions_.size()) {
      pixels_->setPixelColor(j, c);
    }
  }

  pixels_->show();
}

unsigned long InterleavedLedEffect::length() const {
  return length_;
}

void InterleavedLedEffect::pushBack(std::unique_ptr<ColorFunction> f) {
  length_ = std::max(length_, f->length());
  colors_functions_.push_back(std::move(f));
}
