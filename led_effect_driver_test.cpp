#include "led_effect_driver.h"

#include <memory>

#include "gtest/gtest.h"
#include "led_effect.h"

struct BasicLedOutput {
  int begin_count = 0;
  unsigned long last_update_millis = 0;
};

class BasicLedEffect : public LedEffect {
  public:
    BasicLedEffect(BasicLedOutput* out) : output_(out) {}

    void begin() override {
      output_->begin_count++;
    }
    void update(unsigned long millis) override {
      output_->last_update_millis = millis;
    }
  private:
    BasicLedOutput* output_;
};

TEST(LedEffectDriverTest, Begin) {
  BasicLedOutput out;
  LedEffectDriver driver;
  driver.emplaceBack<BasicLedEffect>(&out);

  EXPECT_EQ(out.begin_count, 0);
  driver.begin();
  EXPECT_EQ(out.begin_count, 1);
}

TEST(LedEffectDriverTest, Next) {
  BasicLedOutput out1;
  BasicLedOutput out2;
  LedEffectDriver driver;
  driver.emplaceBack<BasicLedEffect>(&out1);
  driver.emplaceBack<BasicLedEffect>(&out2);

  driver.next(100);
  EXPECT_EQ(out2.begin_count, 1);
  driver.onTimerUpdated(150);
  EXPECT_EQ(out2.last_update_millis, 50);
}

TEST(LedEffectDriverTest, NextOverflow) {
  BasicLedOutput out1;
  BasicLedOutput out2;
  LedEffectDriver driver;
  driver.emplaceBack<BasicLedEffect>(&out1);
  driver.emplaceBack<BasicLedEffect>(&out2);

  driver.begin();
  driver.next(100);
  driver.next(150);
  EXPECT_EQ(out1.begin_count, 2);
  EXPECT_EQ(out2.begin_count, 1);
}

TEST(LedEffectDriverTest, EmptyOperations) {
  LedEffectDriver driver;

  // Does not crash
  driver.begin();
  driver.next(100);
  driver.next(150);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
