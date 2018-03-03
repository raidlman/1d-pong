// Button.h
#ifndef BUTTON_H
#define BUTTON_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

class Button {
  public:
    Button();
    Button(uint8_t pin, uint16_t lock_time);

    void set_pin(uint8_t pin);
    void set_lock_time(double time);
    bool is_pressed();

  private:
    enum ButtonState {
      BUTTON_RELEASED = 0,
      BUTTON_PRESSED
    };

    ButtonState current_state;

    uint8_t pin;
    bool locked;
    unsigned long time;
    unsigned long lock_time;
    void update_state();
  
};

#endif