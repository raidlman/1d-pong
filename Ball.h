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

// Ball.h
#ifndef BALL_H
#define BALL_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include "Player.h"

class Ball {
  public:
    Ball(int8_t position, uint8_t min_position, uint8_t max_position, double speed, int8_t direction);

    bool is_inside_hitbox(Player &player);
    bool timer();
    int8_t get_position();
    int8_t get_previous_position();
    void set_position(int8_t p);
    int8_t get_direction();
    void set_direction(uint8_t direction);
    void reverse_direction();
    void hit();
    void advance();

    void calc_speedup(Player &player);
    void reset_speedup();
    void serve(Player player);

  private:
    int8_t position, previous_position;
    uint8_t min_position, max_position;
    double speed;
    double initial_speed;
    double speedup;
    int8_t direction;
    unsigned long time;

    uint8_t distance_to_field_boundary (Player &player);
    
    // convert speed (in m/s) to timer delay
    uint16_t speed_to_timer();
    void increase_speed();
};

#endif
