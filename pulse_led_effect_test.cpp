#include "pulse_led_effect.h"

#include "gtest/gtest.h"
#include "neopixel.h"
#include "mock_neopixel.h"

TEST(PulseLedEffectTest, UpdateStart) {
  FakeNeopixel<2> pixels;
  color_t color {100, 50, 0, 0};
  PulseLedEffect effect {&pixels, color, 1000};

  effect.update(0);

  color_t color_off {0, 0, 0, 0};
  EXPECT_EQ(pixels.getPixelColor(0), color_off);
  EXPECT_EQ(pixels.getPixelColor(1), color_off);
}

TEST(PulseLedEffectTest, UpdatePeak) {
  FakeNeopixel<2> pixels;
  color_t color {100, 50, 0, 0};
  PulseLedEffect effect {&pixels, color, 1000};

  effect.update(500);

  EXPECT_EQ(pixels.getPixelColor(0), color);
  EXPECT_EQ(pixels.getPixelColor(1), color);
}

TEST(PulseLedEffectTest, UpdateEnd) {
  FakeNeopixel<2> pixels;
  color_t color {100, 50, 0, 0};
  PulseLedEffect effect {&pixels, color, 1000};

  effect.update(1000);

  color_t color_off {0, 0, 0, 0};
  EXPECT_EQ(pixels.getPixelColor(0), color_off);
  EXPECT_EQ(pixels.getPixelColor(1), color_off);
}

TEST(PulseLedEffectTest, UpdateMatches) {
  FakeNeopixel<2> pixels;
  color_t color {100, 50, 0, 0};
  PulseLedEffect effect {&pixels, color, 1000};

  effect.update(400);

  color_t color_pixel {57, 28, 0, 0};
  EXPECT_EQ(pixels.getPixelColor(0), color_pixel);
  EXPECT_EQ(pixels.getPixelColor(1), color_pixel);

  effect.update(600);
  EXPECT_EQ(pixels.getPixelColor(0), color_pixel);
  EXPECT_EQ(pixels.getPixelColor(1), color_pixel);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
