#ifndef PULSE_COLOR_FUNCTION_H
#define PULSE_COLOR_FUNCTION_H

#include "color_function.h"
#include "led_strip.h"

class PulseColorFunction : public ColorFunction {
  public:
    PulseColorFunction(color_t color_end, unsigned long length);
    PulseColorFunction(color_t color_start, color_t color_end, unsigned long length);
    color_t color(unsigned long millis) const override;
    unsigned long length() const override;
  private:
    struct Range {
      Range(uint8_t start, uint8_t end);
      uint8_t operator()(unsigned long millis, unsigned long peak_millis, float ratio) const;
      uint8_t min = 0;
      uint8_t max = 0;
      uint8_t start_index = 0;
      uint8_t end_index = 0;
      bool reverse = false;
    };

    Range r_range_;
    Range g_range_;
    Range b_range_;
    Range w_range_;
    unsigned long length_;
};

#endif
