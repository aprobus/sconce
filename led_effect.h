#ifndef LED_EFFECT_H
#define LED_EFFECT_H

class LedEffect {
  public:
  virtual ~LedEffect() = default;
  virtual void update(unsigned long millis) = 0;
  virtual unsigned long length() const = 0;
};

#endif
