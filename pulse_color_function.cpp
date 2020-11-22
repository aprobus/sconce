#include "pulse_color_function.h"

#include <algorithm>

namespace {
  // Generated from `python3 gamma.py`
  constexpr uint8_t kGammaTableSize = 100;
  constexpr uint8_t kGammaTable[100] = {
      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
      1,  1,  1,  1,  2,  2,  2,  3,  3,  3,
      4,  5,  5,  6,  6,  7,  8,  9, 10, 10,
     11, 12, 14, 15, 16, 17, 18, 20, 21, 23,
     24, 26, 27, 29, 31, 33, 35, 37, 39, 41,
     43, 45, 48, 50, 53, 55, 58, 61, 64, 66,
     69, 72, 76, 79, 82, 85, 89, 92, 96,100,
    104,107,111,115,120,124,128,133,137,142,
    147,151,156,161,166,172,177,182,188,193,
    199,205,211,217,223,229,235,242,248,255,
  };

  uint8_t startIndex(uint8_t color) {
    uint8_t index = 0;
    for (uint8_t delta = kGammaTableSize / 2; delta > 0; delta /= 2) {
      if (kGammaTable[index + delta] < color) {
        index = index + delta;
      }
    }

    if (index < (kGammaTableSize - 1) && kGammaTable[index] != color && kGammaTable[index + 1] == color) {
      index++;
    }

    return index;
  }

  uint8_t endIndex(uint8_t color) {
    uint8_t index = kGammaTableSize - 1;
    for (uint8_t delta = kGammaTableSize / 2; delta > 0; delta /= 2) {
      if (kGammaTable[index - delta] > color) {
        index = index - delta;
      }
    }

    if (index > 0 && kGammaTable[index] != color && kGammaTable[index - 1] == color) {
      index--;
    }

    return index;
  }
}

PulseColorFunction::Range::Range(uint8_t start, uint8_t end) {
  bool reverse = false;
  if (start <= end) {
    min = start;
    max = end;
  } else {
    reverse = true;
    min = end;
    max = start;
  }

  start_index = startIndex(min);
  end_index = endIndex(max);
}

uint8_t PulseColorFunction::Range::operator()(unsigned long millis, unsigned long peak_millis, float ratio) const {
  if (millis == peak_millis) {
    return max;
  }

  uint8_t max_delta = end_index - start_index;
  uint8_t index_delta = std::min<uint8_t>(max_delta, static_cast<uint8_t>(ratio * max_delta));
  uint8_t index = 0;
  if (reverse) {
    index = end_index - index_delta;
  } else {
    index = start_index + index_delta;
  }

  return std::max(std::min(kGammaTable[index], max), min);
}

PulseColorFunction::PulseColorFunction(color_t color_end, unsigned long length) : PulseColorFunction(color_t(0, 0, 0, 0), color_end, length) {}

PulseColorFunction::PulseColorFunction(color_t color_start, color_t color_end, unsigned long length) :
  r_range_(color_start.r, color_end.r),
  g_range_(color_start.g, color_end.g),
  b_range_(color_start.b, color_end.b),
  w_range_(color_start.w, color_end.w),
  length_(length) {
}

color_t PulseColorFunction::color(unsigned long millis) const {
  if (millis >= length_) {
    return {0, 0, 0, 0};
  }

  unsigned long peak_millis = length_ / 2;
  // x ms after peak will be same as x millis before peak
  unsigned long display_millis = millis;
  if (display_millis > peak_millis) {
    display_millis = peak_millis - (millis - peak_millis);
  }

  float ratio = (float)display_millis / peak_millis;

  return color_t(
    r_range_(display_millis, peak_millis, ratio),
    g_range_(display_millis, peak_millis, ratio),
    b_range_(display_millis, peak_millis, ratio),
    w_range_(display_millis, peak_millis, ratio)
  );
}

unsigned long PulseColorFunction::length() const {
  return length_;
}
