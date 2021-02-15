#undef min
#undef max

#include <Adafruit_NeoPixel.h>
#include <vector>

#include "button.h"
#include "color_function_led_effect.h"
#include "const_color_function.h"
#include "led_effect_driver.h"
#include "led_strip.h"
#include "moving_led_effect.h"
#include "neopixel_strip.h"
#include "pulse_color_function.h"
#include "repeated_led_effect.h"
#include "sequential_led_effect.h"

const int num_pixels = 40;
const int neopixel_pin = 7;
const int button_pin = A4;

constexpr bool constTrue(uint16_t x) {
  return true;
}

std::unique_ptr<LedEffect> buildSolidEffect(LedStrip* leds, color_t color) {
  auto effect = std::unique_ptr<ColorFunctionLedEffect>(new ColorFunctionLedEffect(leds));
  auto color_f = std::unique_ptr<ColorFunction>(new ConstColorFunction(color, 1));
  effect->add(std::move(color_f), constTrue);
  return effect;
}

class IsDiv {
  public:
  IsDiv(int x, int y) : x_(x), y_(y) {}

  bool operator()(uint16_t time_millis) {
    return time_millis % x_ == y_;
  }
  private:
  int x_;
  int y_;
};

std::unique_ptr<LedEffect> buildChristmasEffect(LedStrip* leds) {
  auto effect = std::unique_ptr<ColorFunctionLedEffect>(new ColorFunctionLedEffect(leds));

  effect->add(std::unique_ptr<ColorFunction>(new PulseColorFunction(color_t(0, 64, 8, 0), color_t(0, 255, 16, 0), 900)), IsDiv(3, 0));
  effect->add(std::unique_ptr<ColorFunction>(new PulseColorFunction(color_t(64, 0, 0, 0), color_t(255, 8, 0, 0), 1100)), IsDiv(3, 1));
  effect->add(std::unique_ptr<ColorFunction>(new PulseColorFunction(color_t(0, 0, 0, 16), color_t(0, 0, 0, 64), 1300)), IsDiv(3, 2));

  return effect;
}

void setup() {
  // Section - Allocate
  Adafruit_NeoPixel raw_pixels{num_pixels, neopixel_pin, NEO_GRBW};
  NeopixelStrip pixels(&raw_pixels);

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

  led_driver.pushBack(buildSolidEffect(&pixels, color_off));
  led_driver.pushBack(buildSolidEffect(&pixels, color_white));

  led_driver.pushBack(buildChristmasEffect(&pixels));

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
