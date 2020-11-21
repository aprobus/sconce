#ifndef MOCK_LED_EFFECT_H
#define MOCK_LED_EFFECT_H

#include "gmock/gmock.h"
#include "led_effect.h"

class MockLedEffect : public LedEffect {
  public:
  MOCK_METHOD(void, update, (unsigned long), (override));
  MOCK_METHOD(unsigned long, length, (), (const override));
};

#endif
