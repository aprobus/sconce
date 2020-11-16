#include "button.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
int digitalRead(int i) {
  return 0;
}
void pinMode(int i, int x) { }
constexpr int HIGH = 1;
constexpr int INPUT = 0;
#endif

Button::Button(int pin) : pin_(pin) {
}

void Button::begin() {
  pinMode(pin_, INPUT);
}

bool Button::captureClick() {
  bool did_click = false;
  if (digitalRead(pin_) == HIGH) {
    did_rise_ = true;
  } else if (did_rise_) {
    did_rise_ = false;
    did_click = true;
  }

  return did_click;
}
