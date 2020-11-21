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
  color_t color_green = {0, 255, 0, 0};
  color_t color_red = {255, 0, 0, 0};
  color_t color_blue = {0, 0, 255, 0};

  led_driver.emplaceBack<SolidLedEffect>(&pixels, color_off);
  led_driver.emplaceBack<SolidLedEffect>(&pixels, color_white);
  led_driver.emplaceBack<MovingLedEffect>(&pixels, color_orange, 500);

  auto christmas_seq = std::unique_ptr<InterleavedLedEffect>(new InterleavedLedEffect(&pixels));
  christmas_seq->emplaceBack<PulseColorFunction>(color_green, 1000);
  christmas_seq->emplaceBack<PulseColorFunction>(color_red, 1000);
  christmas_seq->emplaceBack<PulseColorFunction>(color_white, 1000);
  auto christmas_effect = std::unique_ptr<WrappedRepeatedLedEffect>(new WrappedRepeatedLedEffect(std::move(christmas_seq)));
  led_driver.pushBack(std::move(christmas_effect));

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
