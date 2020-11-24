#undef min
#undef max

#include <Adafruit_NeoPixel.h>
#include <vector>

#include "button.h"
#include "interleaved_led_effect.h"
#include "led_effect_driver.h"
#include "moving_led_effect.h"
#include "neopixel.h"
#include "neopixel_wrapper.h"
#include "pulse_color_function.h"
#include "repeated_led_effect.h"
#include "sequential_led_effect.h"
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
  color_t color_white = {0, 0, 0, 255};
  color_t color_orange = {255, 128, 0, 64};
  color_t color_red = {255, 0, 0, 0};
  color_t color_blue = {0, 0, 255, 0};

  led_driver.emplaceBack<SolidLedEffect>(&pixels, color_off);
  led_driver.emplaceBack<SolidLedEffect>(&pixels, color_white);

  auto christmas_seq = std::unique_ptr<InterleavedLedEffect>(new InterleavedLedEffect(&pixels));
  christmas_seq->emplaceBack<PulseColorFunction>(color_t(0, 64, 8, 0), color_t(0, 255, 16, 0), 900);
  christmas_seq->emplaceBack<PulseColorFunction>(color_t(64, 0, 0, 0), color_t(255, 8, 0, 0), 1100);
  christmas_seq->emplaceBack<PulseColorFunction>(color_t(0, 0, 0, 16), color_t(0, 0, 0, 64), 1300);
  led_driver.pushBack(std::move(christmas_seq));

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
