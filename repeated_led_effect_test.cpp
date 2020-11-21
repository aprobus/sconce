#include "repeated_led_effect.h"

#include <memory>

#include "gtest/gtest.h"
#include "mock_led_effect.h"

using ::testing::Eq;
using ::testing::Return;

TEST(RepeatedLedEffect, Update) {
  auto mock_effect = std::unique_ptr<MockLedEffect>(new MockLedEffect());
  EXPECT_CALL(*mock_effect, length()).WillOnce(Return(10));
  EXPECT_CALL(*mock_effect, update(Eq(8)));
  WrappedRepeatedLedEffect effect(std::move(mock_effect));
  effect.update(8);
}

TEST(RepeatedLedEffect, UpdateOverflow) {
  auto mock_effect = std::unique_ptr<MockLedEffect>(new MockLedEffect());
  EXPECT_CALL(*mock_effect, length()).WillOnce(Return(10));
  EXPECT_CALL(*mock_effect, update(Eq(8)));
  WrappedRepeatedLedEffect effect(std::move(mock_effect));
  effect.update(18);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
