#ifndef PULSE_COLOR_FUNCTION_H
#define PULSE_COLOR_FUNCTION_H

#include "color_function.h"
#include "neopixel.h"

class PulseColorFunction : public ColorFunction {
  public:
    PulseColorFunction(color_t color, unsigned long length);
    color_t operator()(unsigned long millis) const override;
    unsigned long length() const override;
  private:
    color_t color_;
    unsigned long length_;
};

#endif
