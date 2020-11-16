#include "repeated_led_effect.h"

#include <memory>

#include "gtest/gtest.h"
#include "led_effect.h"

class MockEffect : public TimedLedEffect {
  public:
  MockEffect(unsigned long* millis) : last_millis_(millis) {}

  void update(unsigned long millis) override {
    *last_millis_ = millis;
  }

  unsigned long length() const override {
    return 100;
  }

  unsigned long* last_millis_;
};

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
