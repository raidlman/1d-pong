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