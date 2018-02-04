#include "Button.h"

Button::Button() {
}

Button::Button(uint8_t pin, uint16_t lock_time) {
  this->pin = pin;
  this->lock_time = lock_time;
}

void Button::update_state(){
  if ( digitalRead(pin) == HIGH && millis() - time >= lock_time ) {
      current_state = BUTTON_PRESSED;
      time = millis();
  } else {
    current_state = BUTTON_RELEASED;
  }
}

void Button::set_pin (uint8_t p) {
  pin = p;
  pinMode(p, INPUT);
}

void Button::set_lock_time(double t) {
  lock_time = t;
}

bool Button::is_pressed() {
  update_state();
  if ( current_state == BUTTON_PRESSED ) {
    return true;
  }
  return false;
}