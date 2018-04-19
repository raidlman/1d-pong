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

// Screen.h
#ifndef SCREEN_H
#define SCREEN_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <FastLED.h>
#include "Ball.h"
#include "Player.h"

class Screen {
  public:
    Screen(uint8_t num_leds, uint8_t brightness);

    void show_score(Player &p1, Player &p2);
    void advance_ball(Ball &b, Player &p1, Player &p2);
    void draw(Player &player_1, Player &player_2, Ball &ball);
    void clear(Ball &ball);

  private:
    uint8_t num_leds;
    CRGB *leds;
    //ESPIChipsets led_type;
    //EOrder led_color_order;
    uint8_t brightness;

    void init();
    void draw_player_score(Player p);
    void clear_led(uint8_t num);
    void draw_ball(uint8_t num);
};

#endif
