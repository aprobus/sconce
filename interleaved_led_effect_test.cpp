#include "interleaved_led_effect.h"

#include <memory>

#include "gtest/gtest.h"
#include "mock_led_effect.h"
#include "mock_neopixel.h"
#include "neopixel.h"

using ::testing::Eq;
using ::testing::Return;

TEST(InterleavedLedEffectTest, Begin) {
  FakeNeopixel<2> pixels;
  InterleavedLedEffect effect {&pixels};

  color_t pixel_color (20, 11, 3, 1);

  auto cf = std::unique_ptr<MockColorFunction>(new MockColorFunction());
  EXPECT_CALL(*cf, length()).WillOnce(Return(10));
  EXPECT_CALL(*cf, color(Eq(0))).WillOnce(Return(pixel_color));
  effect.pushBack(std::move(cf));

  effect.update(0);
  EXPECT_EQ(pixels.getPixelColor(0), pixel_color);
  EXPECT_EQ(pixels.getPixelColor(1), pixel_color);
}

TEST(InterleavedLedEffectTest, MultiFunction) {
  FakeNeopixel<3> pixels;
  InterleavedLedEffect effect {&pixels};

  color_t pixel_color (20, 11, 3, 1);
  color_t alt_pixel_color (99, 100, 1, 0);

  auto cf1 = std::unique_ptr<MockColorFunction>(new MockColorFunction());
  EXPECT_CALL(*cf1, length()).WillOnce(Return(10));
  EXPECT_CALL(*cf1, color(Eq(0))).WillOnce(Return(pixel_color));
  effect.pushBack(std::move(cf1));

  auto cf2 = std::unique_ptr<MockColorFunction>(new MockColorFunction());
  EXPECT_CALL(*cf2, length()).WillOnce(Return(10));
  EXPECT_CALL(*cf2, color(Eq(0))).WillOnce(Return(alt_pixel_color));
  effect.pushBack(std::move(cf2));

  effect.update(0);
  EXPECT_EQ(pixels.getPixelColor(0), pixel_color);
  EXPECT_EQ(pixels.getPixelColor(1), alt_pixel_color);
  EXPECT_EQ(pixels.getPixelColor(2), pixel_color);
}

TEST(InterleavedLedEffectTest, MultiMismatchedLength) {
  FakeNeopixel<3> pixels;
  InterleavedLedEffect effect {&pixels};

  auto cf1 = std::unique_ptr<MockColorFunction>(new MockColorFunction());
  EXPECT_CALL(*cf1, length()).WillOnce(Return(10));
  effect.pushBack(std::move(cf1));

  auto cf2 = std::unique_ptr<MockColorFunction>(new MockColorFunction());
  EXPECT_CALL(*cf2, length()).WillOnce(Return(15));
  effect.pushBack(std::move(cf2));

  EXPECT_EQ(effect.length(), 15);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
