#undef min
#undef max

#include <Adafruit_NeoPixel.h>
#include <vector>

#include "button.h"
#include "led_effect_driver.h"
#include "moving_led_effect.h"
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

  LedEffectDriver led_driver;

  color_t color_off = {0, 0, 0, 0};
  led_driver.emplaceBack<SolidLedEffect>(&pixels, color_off);

  color_t color_white = {0, 0, 0, 255};
  led_driver.emplaceBack<SolidLedEffect>(&pixels, color_white);

  color_t color_orange = {255, 128, 0, 0};
  led_driver.emplaceBack<MovingLedEffect>(&pixels, color_orange, 500);

  led_driver.begin();

  // Section - Loop
  while(true) {
    /*delay(500);*/
    unsigned long now = millis();

    if (button.captureClick()) {
      led_driver.next(now);
    } else {
      led_driver.onTimerUpdated(now);
    }
  }
}

void loop() {
}
