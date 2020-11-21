#include "pulse_color_function.h"

#include "gtest/gtest.h"
#include "neopixel.h"

TEST(PulseColorFunctionTest, Initial) {
  color_t color {100, 50, 0, 0};
  PulseColorFunction effect {color, 1000};

  color_t color_off {0, 0, 0, 0};
  EXPECT_EQ(effect.color(0), color_off);
}

TEST(PulseColorFunctionTest, Peak) {
  color_t color {100, 50, 0, 0};
  PulseColorFunction effect {color, 1000};

  EXPECT_EQ(effect.color(500), color);
}

TEST(PulseColorFunctionTest, Matches) {
  color_t color {100, 50, 0, 0};
  PulseColorFunction effect {color, 1000};

  EXPECT_EQ(effect.color(400), effect.color(600));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
