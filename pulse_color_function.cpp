#include "pulse_color_function.h"

#include <algorithm>

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

PulseColorFunction::PulseColorFunction(color_t color, unsigned long length) : color_(color), length_(length) {}

color_t PulseColorFunction::operator()(unsigned long millis) const {
  if (millis >= length_) {
    return {0, 0, 0, 0};
  } else if (millis == 0) {
    return {0, 0, 0, 0};
  }

  unsigned long peak_millis = length_ / 2;
  // x ms after peak will be same as x millis before peak
  unsigned long display_millis = millis;
  if (display_millis > peak_millis) {
    display_millis = peak_millis - (millis - peak_millis);
  }

  int completion_percent = static_cast<int>(display_millis * 100 / peak_millis);
  return {
    scale_color(color_.r, completion_percent),
    scale_color(color_.g, completion_percent),
    scale_color(color_.b, completion_percent),
    scale_color(color_.w, completion_percent)
  };
}

unsigned long PulseColorFunction::length() const {
  return length_;
}
