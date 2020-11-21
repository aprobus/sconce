#include "pulse_led_effect.h"

#include "neopixel.h"
#include "pulse_color_function.h"

PulseLedEffect::PulseLedEffect(Neopixel* pixels, PulseColorFunction f) : pixels_(pixels), pulse_function_(f) {}

void PulseLedEffect::update(unsigned long millis) {
  if (millis >= pulse_function_.length()) {
    return;
  }

  color_t color = pulse_function_(millis);

  for (int i = 0; i < pixels_->numPixels(); i++) {
    pixels_->setPixelColor(i, color);
  }

  pixels_->show();
}

unsigned long PulseLedEffect::length() const {
  return pulse_function_.length();
}
