#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(int pin);
    void begin();
    bool captureClick();

  private:
    int pin_;
    bool did_rise_ = false;
};

#endif
