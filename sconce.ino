#undef min
#undef max

#include <Adafruit_NeoPixel.h>

#include "neopixel.h"
#include "neopixel_wrapper.h"
#include "button.h"

const int num_pixels = 40;
const int neopixel_pin = 7;
const int button_pin = A4;

void setup() {
  // Section - Allocate
  Adafruit_NeoPixel raw_pixels{num_pixels, neopixel_pin, NEO_GRBW};
  NeopixelWrapper pixels(&raw_pixels);

  Button button(button_pin);

  // Section - Initialize
  Serial.begin(9600);
  button.begin();
  raw_pixels.begin();
  raw_pixels.clear();

  color_t color_white = {0, 0, 0, 255};
  color_t color_off = {0, 0, 0, 0};

  bool is_on = true;
  setAllPixels(&pixels, color_white);

  // Section - Loop
  while(true) {
    /*delay(500);*/

    if (button.captureClick()) {
      is_on = !is_on;

      if (is_on) {
        setAllPixels(&pixels, color_white);
      } else {
        setAllPixels(&pixels, color_off);
      }
    }
  }
}

void setAllPixels(Neopixel* pixels, color_t color) {
  for (int i = 0; i < pixels->numPixels(); i += 1) {
    pixels->setPixelColor(i, color);
  }
  pixels->show();
}

void loop() {
}
