#undef min
#undef max

#include <Adafruit_NeoPixel.h>
#include <vector>

#include "button.h"
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

  color_t color_white = {0, 0, 0, 255};
  SolidLedEffect full_on_effect {&pixels, color_white};

  color_t color_off = {0, 0, 0, 0};
  SolidLedEffect full_off_effect {&pixels, color_off};

  color_t color_orange = {255, 128, 0, 0};
  MovingLedEffect rotating_effect {&pixels, color_orange, 500};

  std::vector<LedEffect*> led_effects;
  led_effects.push_back(&full_on_effect);
  led_effects.push_back(&full_off_effect);
  led_effects.push_back(&rotating_effect);

  int mode = 0;
  led_effects[0]->begin();

  // Section - Loop
  unsigned long switched_at_millis = millis();
  while(true) {
    /*delay(500);*/
    unsigned long now = millis();

    if (button.captureClick()) {
      switched_at_millis = now;
      mode = (mode + 1) % led_effects.size();
      led_effects[mode]->begin();
    } else {
      led_effects[mode]->update(millis() - switched_at_millis);
    }
  }
}

void loop() {
}
