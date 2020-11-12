#undef min
#undef max

#include <Adafruit_NeoPixel.h>

#include "button.h"
#include "neopixel.h"
#include "neopixel_wrapper.h"
#include "solid_led_effect.h"

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
  SolidLedEffect full_on_effect {&pixels, color_white};

  color_t color_off = {0, 0, 0, 0};
  SolidLedEffect full_off_effect {&pixels, color_off};

  bool is_on = true;
  full_on_effect.begin();

  // Section - Loop
  while(true) {
    /*delay(500);*/

    if (button.captureClick()) {
      is_on = !is_on;

      if (is_on) {
        full_on_effect.begin();
      } else {
        full_off_effect.begin();
      }
    }
  }
}

void loop() {
}
