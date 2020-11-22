#include "pulse_color_function.h"

#include "gtest/gtest.h"
#include "neopixel.h"

TEST(PulseColorFunctionTest, Initial) {
  color_t color {100, 50, 0, 0};
  PulseColorFunction effect {color, 1000};

  color_t color_off {0, 0, 0, 0};
  EXPECT_EQ(effect.color(0), color_off);
}

TEST(PulseColorFunctionTest, RangeInitial) {
  color_t color_start {50, 50, 50, 50};
  color_t color_end {100, 100, 100, 100};
  PulseColorFunction effect {color_start, color_end, 1000};

  EXPECT_EQ(effect.color(0), color_start);
}

TEST(PulseColorFunctionTest, Peak) {
  color_t color {100, 50, 0, 0};
  PulseColorFunction effect {color, 1000};

  EXPECT_EQ(effect.color(500), color);
}

TEST(PulseColorFunctionTest, RangePeak) {
  color_t color_start {50, 0, 0, 254};
  color_t color_end {100, 255, 1, 255};
  PulseColorFunction effect {color_start, color_end, 1000};

  EXPECT_EQ(effect.color(500), color_end);
}

TEST(PulseColorFunctionTest, Matches) {
  color_t color {100, 50, 0, 0};
  PulseColorFunction effect {color, 1000};

  EXPECT_EQ(effect.color(400), effect.color(600));
}

TEST(PulseColorFunctionTest, ColorRate) {
  color_t color {255, 0, 0, 0};
  PulseColorFunction effect {color, 1000};

  EXPECT_EQ(effect.color(100).r, 3);
  EXPECT_EQ(effect.color(200).r, 23);
  EXPECT_EQ(effect.color(300).r, 66);
  EXPECT_EQ(effect.color(400).r, 142);
}

TEST(PulseColorFunctionTest, RangeRate) {
  color_t color_start {50, 0, 0, 0};
  color_t color_end {100, 0, 0, 0};
  PulseColorFunction effect {color_start, color_end, 1000};

  EXPECT_EQ(effect.color(100).r, 53);
  EXPECT_EQ(effect.color(200).r, 64);
  EXPECT_EQ(effect.color(300).r, 72);
  EXPECT_EQ(effect.color(400).r, 85);
}

TEST(PulseColorFunctionTest, RangeFullCycle) {
  color_t color_start {0, 0, 0, 0};
  color_t color_end {255, 0, 0, 0};
  PulseColorFunction effect {color_start, color_end, 10};

  EXPECT_EQ(effect.color(0).r, 0);
  EXPECT_EQ(effect.color(1).r, 3);
  EXPECT_EQ(effect.color(2).r, 23);
  EXPECT_EQ(effect.color(3).r, 66);
  EXPECT_EQ(effect.color(4).r, 142);
  EXPECT_EQ(effect.color(5).r, 255);
  EXPECT_EQ(effect.color(6).r, 142);
  EXPECT_EQ(effect.color(7).r, 66);
  EXPECT_EQ(effect.color(8).r, 23);
  EXPECT_EQ(effect.color(9).r, 3);
}

TEST(PulseColorFunctionTest, RangeRateDesc) {
  color_t color_start {100, 0, 0, 0};
  color_t color_end {50, 0, 0, 0};
  PulseColorFunction effect {color_start, color_end, 1000};

  EXPECT_EQ(effect.color(100).r, 53);
  EXPECT_EQ(effect.color(200).r, 64);
  EXPECT_EQ(effect.color(300).r, 72);
  EXPECT_EQ(effect.color(400).r, 85);
}

// Verifies that colors are monotonically increasing from start to peak.
TEST(PulseColorFunctionTest, ColorIncrements) {
  color_t color_end {255, 100, 1, 89};
  PulseColorFunction effect {color_end, 1000};

  color_t previous_color(0, 0, 0, 0);
  for (int i = 0; i <= 500; i++) {
    color_t next_color = effect.color(i);
    EXPECT_GE(next_color.r, previous_color.r) << i;
    EXPECT_GE(next_color.g, previous_color.g) << i;
    EXPECT_GE(next_color.b, previous_color.b) << i;
    EXPECT_GE(next_color.w, previous_color.w) << i;
    previous_color = next_color;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
