#include "moving_led_effect.h"

#include "gtest/gtest.h"
#include "led_strip.h"
#include "mock_led_strip.h"

TEST(MovingLedEffectTest, Begin) {
  FakeLedStrip<10> pixels;
  color_t color {34, 1, 2, 10};
  MovingLedEffect effect {&pixels, color, 10};

  effect.update(0);

  EXPECT_EQ(pixels.getPixelColor(0), color);
  EXPECT_NE(pixels.getPixelColor(1), color);
}

TEST(MovingLedEffectTest, UpdateBeforeSwitch) {
  FakeLedStrip<10> pixels;
  color_t color {34, 1, 2, 10};
  MovingLedEffect effect {&pixels, color, 10};

  effect.update(9);
  EXPECT_EQ(pixels.getPixelColor(0), color);
  EXPECT_NE(pixels.getPixelColor(1), color);
}

TEST(MovingLedEffectTest, UpdateOnSwitch) {
  FakeLedStrip<10> pixels;
  color_t color {34, 1, 2, 10};
  MovingLedEffect effect {&pixels, color, 10};

  effect.update(10);
  EXPECT_NE(pixels.getPixelColor(0), color);
  EXPECT_EQ(pixels.getPixelColor(1), color);
}

TEST(MovingLedEffectTest, UpdateOnRollOver) {
  FakeLedStrip<10> pixels;
  color_t color {34, 1, 2, 10};
  MovingLedEffect effect {&pixels, color, 10};

  effect.update(100);
  EXPECT_EQ(pixels.getPixelColor(0), color);
  EXPECT_NE(pixels.getPixelColor(1), color);
  EXPECT_NE(pixels.getPixelColor(9), color);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
