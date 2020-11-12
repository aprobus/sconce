#ifndef LED_EFFECT_H
#define LED_EFFECT_H

class LedEffect {
  public:
  virtual ~LedEffect() = default;
  virtual void begin() = 0;
  virtual void update(unsigned long millis) {};
};

#endif