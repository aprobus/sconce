#include "solid_led_effect.h"

#include <limits>

#include "led_strip.h"

SolidLedEffect::SolidLedEffect(LedStrip* pixels, color_t color) : pixels_(pixels), color_(color) {}

void SolidLedEffect::update(unsigned long millis) {
  for (int i = 0; i < pixels_->numPixels(); i++) {
    pixels_->setPixelColor(i, color_);
  }
  pixels_->show();
}

unsigned long SolidLedEffect::length() const {
  return std::numeric_limits<unsigned long>::max();
}
