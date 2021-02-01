#ifndef COLOR_FUNCTION_H
#define COLOR_FUNCTION_H

#include "led_strip.h"

class ColorFunction {
  public:
    virtual ~ColorFunction() = default;
    virtual color_t color(unsigned long millis) const = 0;
    virtual unsigned long length() const = 0;
};

#endif
