// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class Button {
  enum ButtonState {
      BUTTON_RELEASED = 0,
      BUTTON_PRESSED
    };
  
  private:
    ButtonState current_state;
    uint8_t pin;
    bool lock;
    unsigned long time;
    unsigned long lock_time;

    void update_state();

  public:
    void set_pin (uint8_t p);
    void set_lock_time(double t);
    bool is_pressed();
};

#endif