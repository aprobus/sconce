#include "solid_led_effect.h"

#include "gtest/gtest.h"
#include "neopixel.h"
#include "mock_neopixel.h"

TEST(SolidLedEffectTest, Update) {
  FakeNeopixel<10> pixels;
  color_t color {34, 1, 2, 10};
  SolidLedEffect effect {&pixels, color};

  for (int i = 0; i < pixels.numPixels(); i++) {
    EXPECT_NE(pixels.getPixelColor(i), color);
  }

  effect.update(0);

  for (int i = 0; i < pixels.numPixels(); i++) {
    EXPECT_EQ(pixels.getPixelColor(i), color);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}