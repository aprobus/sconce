#include "button.h"

#include <Arduino.h>

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
