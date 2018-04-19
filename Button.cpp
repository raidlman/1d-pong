/*
 * 1D Pong - Pong-like game run on an Arduino MCU
 * Copyright (C) 2018  Stephan Riedel - raidlman@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// Button.cpp
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

void Button::set_pin (uint8_t pin) {
  this->pin = pin;
  pinMode(pin, INPUT);
}

void Button::set_lock_time(double time) {
  lock_time = time;
}

bool Button::is_pressed() {
  update_state();
  if ( current_state == BUTTON_PRESSED ) {
    return true;
  }
  return false;
}