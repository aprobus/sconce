#undef min
#undef max

#include <Adafruit_NeoPixel.h>

#include "neopixel.h"
#include "neopixel_wrapper.h"

const int num_pixels = 40;
const int neopixel_pin = 7;
const int button_pin = A4;

void setup() {
  // Section - Allocate
  Adafruit_NeoPixel raw_pixels{num_pixels, neopixel_pin, NEO_GRBW};
  NeopixelWrapper pixels(&raw_pixels);
  pinMode(button_pin, INPUT);

  // Section - Initialize
  Serial.begin(9600);
  raw_pixels.begin();
  raw_pixels.clear();

  color_t pixel_color = {0, 0, 0, 255};
  /*pixels.setPixelColor(0, pixel_color);*/
  /*for (int i = 30; i < 47; i++) {*/
    /*pixels.setPixelColor(i, pixel_color);*/
  /*}*/

  for (int i = 0; i < num_pixels; i += 1) {
    pixels.setPixelColor(i, pixel_color);
  }
  pixels.show();

  // Section - Loop
  while(true) {
    delay(500);
    if (digitalRead(button_pin) == HIGH) {
      Serial.write("high\n");
    } else {
      Serial.write("low\n");
    }
  }
}

void loop() {
}
