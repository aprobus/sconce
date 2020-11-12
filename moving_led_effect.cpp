#include "moving_led_effect.h"

#include "neopixel.h"

namespace {
  constexpr color_t kColorOff {0, 0, 0, 0};
}

MovingLedEffect::MovingLedEffect(Neopixel* pixels, color_t color, unsigned long millis_per_pixel) : pixels_(pixels), color_(color), millis_per_pixel_(millis_per_pixel) {}

void MovingLedEffect::begin() {
  pixels_->clear();
  index_ = 0;

  pixels_->setPixelColor(index_, color_);
}

void MovingLedEffect::update(unsigned long millis) {
  uint16_t current_index = (millis / millis_per_pixel_) % pixels_->numPixels();
  if (current_index == index_) return;

  pixels_->setPixelColor(index_, kColorOff);
  index_ = current_index;
  pixels_->setPixelColor(index_, color_);
  pixels_->show();
}