#ifndef MOCK_LED_EFFECT_H
#define MOCK_LED_EFFECT_H

#include "color_function.h"
#include "gmock/gmock.h"
#include "led_effect.h"
#include "led_strip.h"

class MockLedEffect : public LedEffect {
  public:
  MOCK_METHOD(void, update, (unsigned long), (override));
  MOCK_METHOD(unsigned long, length, (), (const override));
};

class MockColorFunction : public ColorFunction {
  public:
  MOCK_METHOD(color_t, color, (unsigned long), (const override));
  MOCK_METHOD(unsigned long, length, (), (const override));
};

#endif
