#include "moving_led_effect.h"

#include "neopixel.h"

MovingLedEffect::MovingLedEffect(Neopixel* pixels, color_t color, unsigned long millis_per_pixel) : pixels_(pixels), color_(color), millis_per_pixel_(millis_per_pixel) {}

void MovingLedEffect::update(unsigned long millis) {
  pixels_->clear();

  uint16_t current_index = (millis / millis_per_pixel_) % pixels_->numPixels();
  pixels_->setPixelColor(current_index, color_);
  pixels_->show();
}