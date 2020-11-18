#include "repeated_led_effect.h"

#include <memory>

#include "gtest/gtest.h"
#include "mock_led_effect.h"

TEST(RepeatedLedEffect, Update) {
  unsigned long out = 0;
  RepeatedLedEffect<MockEffect> effect(&out);
  effect.update(50);
  EXPECT_EQ(out, 50);
}

TEST(RepeatedLedEffect, UpdateOverflow) {
  unsigned long out = 0;
  RepeatedLedEffect<MockEffect> effect(&out);
  effect.update(150);
  EXPECT_EQ(out, 50);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
