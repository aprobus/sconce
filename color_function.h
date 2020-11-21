#ifndef COLOR_FUNCTION_H
#define COLOR_FUNCTION_H

#include "neopixel.h"

class ColorFunction {
  public:
    virtual ~ColorFunction() = default;
    virtual color_t operator()(unsigned long) const = 0;
    virtual unsigned long length() const = 0;
};

#endif
