#include "pulse_led_effect.h"

#include <stdint.h>

#include <algorithm>

#include "neopixel.h"

PulseLedEffect::PulseLedEffect(Neopixel* pixels, color_t color, unsigned long pulse_millis) : pixels_(pixels), color_(color), pulse_millis_(pulse_millis) {}

namespace {
  // Generated from `python3 gamma.py`
  constexpr uint8_t kGammaPercentTable[100] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  1,  1,  1,  1,  1,  1,  1,
     2,  2,  2,  2,  3,  3,  3,  3,  4,  4,
     4,  5,  5,  6,  6,  7,  7,  8,  8,  9,
     9, 10, 11, 11, 12, 13, 14, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
    27, 28, 30, 31, 32, 33, 35, 36, 38, 39,
    41, 42, 44, 45, 47, 49, 50, 52, 54, 56,
    57, 59, 61, 63, 65, 67, 69, 71, 74, 76,
    78, 80, 83, 85, 87, 90, 92, 95, 97,100,
  };

  uint8_t scale_color(uint8_t color, int percent) {
    int index = std::max<int>(std::min<int>(percent, 99), 0);
    return static_cast<uint8_t>(color * static_cast<float>(kGammaPercentTable[index]) / 100.0);
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

  int completion_percent = static_cast<int>(current_millis * 100 / peak_millis);
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
