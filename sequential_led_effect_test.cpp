#include "sequential_led_effect.h"

#include "gtest/gtest.h"
#include "mock_led_effect.h"

TEST(SequentialLedEffectTest, Length) {
  SequentialLedEffect seq_effect;
  unsigned long timer1 = 0;
  unsigned long timer2 = 0;
  seq_effect.emplaceBack<MockEffect>(&timer1);
  seq_effect.emplaceBack<MockEffect>(&timer2);

  EXPECT_EQ(seq_effect.length(), 200);
}

TEST(SequentialLedEffectTest, Update) {
  SequentialLedEffect seq_effect;
  unsigned long timer1 = 0;
  unsigned long timer2 = 5000;
  seq_effect.emplaceBack<MockEffect>(&timer1);
  seq_effect.emplaceBack<MockEffect>(&timer2);

  seq_effect.update(99);
  EXPECT_EQ(timer1, 99);
  EXPECT_EQ(timer2, 5000);

  seq_effect.update(100);
  EXPECT_EQ(timer1, 99);
  EXPECT_EQ(timer2, 0);
}

TEST(SequentialLedEffectTest, UpdateThree) {
  SequentialLedEffect seq_effect;
  unsigned long timer1 = 0;
  unsigned long timer2 = 0;
  unsigned long timer3 = 0;
  seq_effect.emplaceBack<MockEffect>(&timer1);
  seq_effect.emplaceBack<MockEffect>(&timer2);
  seq_effect.emplaceBack<MockEffect>(&timer3);

  seq_effect.update(99);
  EXPECT_EQ(timer1, 99);
  EXPECT_EQ(timer2, 0);
  EXPECT_EQ(timer3, 0);

  seq_effect.update(100);
  EXPECT_EQ(timer1, 99);
  EXPECT_EQ(timer2, 0);
  EXPECT_EQ(timer3, 0);

  seq_effect.update(199);
  EXPECT_EQ(timer1, 99);
  EXPECT_EQ(timer2, 99);
  EXPECT_EQ(timer3, 0);

  seq_effect.update(201);
  EXPECT_EQ(timer1, 99);
  EXPECT_EQ(timer2, 99);
  EXPECT_EQ(timer3, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}