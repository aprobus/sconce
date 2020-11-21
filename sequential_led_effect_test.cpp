#include "sequential_led_effect.h"

#include <memory>

#include "gtest/gtest.h"
#include "mock_led_effect.h"

using ::testing::Eq;
using ::testing::Return;

TEST(SequentialLedEffectTest, Length) {
  SequentialLedEffect seq_effect;

  auto effect_1 = std::unique_ptr<MockLedEffect>(new MockLedEffect());
  auto effect_2 = std::unique_ptr<MockLedEffect>(new MockLedEffect());
  EXPECT_CALL(*effect_1, length()).WillOnce(Return(50));
  EXPECT_CALL(*effect_2, length()).WillOnce(Return(75));

  seq_effect.pushBack(std::move(effect_1));
  seq_effect.pushBack(std::move(effect_2));

  EXPECT_EQ(seq_effect.length(), 125);
}

TEST(SequentialLedEffectTest, Update) {
  SequentialLedEffect seq_effect;

  std::vector<std::unique_ptr<MockLedEffect>> mock_effects;
  for (int i = 0; i < 7; i++) {
    mock_effects.push_back(std::unique_ptr<MockLedEffect>(new MockLedEffect()));
    EXPECT_CALL(*mock_effects.back(), length).WillRepeatedly(Return(10));
    EXPECT_CALL(*mock_effects.back(), update(Eq(i)));
  }

  for (int i = 0; i < mock_effects.size(); i++) {
    seq_effect.pushBack(std::move(mock_effects[i]));
  }

  // Increment by 11 to ensure each effect receives a unique time.
  for (int i = 0; i < 70; i += 11) {
    seq_effect.update(i);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
