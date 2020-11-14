#include "pulse_led_effect.h"

#include <stdint.h>

#include "neopixel.h"

PulseLedEffect::PulseLedEffect(Neopixel* pixels, color_t color, unsigned long pulse_millis) : pixels_(pixels), color_(color), pulse_millis_(pulse_millis) {}

namespace {
  uint8_t scale_color(uint8_t color, float percent) {
    return static_cast<uint8_t>(color * percent);
  }
}

void PulseLedEffect::begin() {
  update(0);
}

void PulseLedEffect::update(unsigned long millis) {
  unsigned long current_millis = millis % pulse_millis_;

  if (current_millis == 0) {
    pixels_->clear();
    return;
  }

  unsigned long peak_millis = pulse_millis_ / 2;
  // x ms after peak will be same as x millis before peak
  if (current_millis > peak_millis) {
    current_millis = peak_millis - (current_millis - peak_millis);
  }

  float completion_percent = ((float)current_millis) / peak_millis;
  color_t actual_color = {
    scale_color(color_.r, completion_percent),
    scale_color(color_.g, completion_percent),
    scale_color(color_.b, completion_percent),
    scale_color(color_.w, completion_percent)
  };

  for (int i = 0; i < pixels_->numPixels(); i++) {
    pixels_->setPixelColor(i, actual_color);
  }
  pixels_->show();
}
