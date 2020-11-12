#include "solid_led_effect.h"

#include "neopixel.h"

SolidLedEffect::SolidLedEffect(Neopixel* pixels, color_t color) : pixels_(pixels), color_(color) {}

void SolidLedEffect::begin() {
  pixels_->clear();
  for (int i = 0; i < pixels_->numPixels(); i++) {
    pixels_->setPixelColor(i, color_);
  }
  pixels_->show();
}