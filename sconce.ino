#undef min
#undef max

#include <Adafruit_NeoPixel.h>

#include "neopixel.h"
#include "neopixel_wrapper.h"

const int num_pixels = 12;
const int neopixel_pin = 6;

void setup() {
  // Section - Allocate
  Adafruit_NeoPixel raw_pixels{num_pixels, neopixel_pin, NEO_GRBW};
  NeopixelWrapper pixels(&raw_pixels);

  // Section - Initialize
  Serial.begin(9600);
  raw_pixels.begin();

  color_t pixel_color = {64, 64, 64, 255};
  pixels.setPixelColor(0, pixel_color);

  // Section - Loop
  while(true) {
    pixels.show();
  }
}

void loop() {
}
