/*
   1D Pong - Pong-like game run on an Arduino MCU
   Copyright (C) 2018  Stephan Riedel - raidlman@gmail.com

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Pong.h
#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Button.h"
#include "Ball.h"
#include "Player.h"
#include "Screen.h"

class Pong {
  public:
    Pong(uint8_t player_1_pin, uint8_t player_2_pin, uint8_t lifes, uint16_t button_lock_time,
         uint8_t num_leds, double stripe_length, uint8_t brightness,
         uint8_t restart_pin, uint16_t restart_lock_time, uint8_t random_seed_pin);

    void game_logic();

  private:
    enum State {
      IDLE = 0,
      DEMO,
      PLAYING,
      SERVE,
      WAITING
    } state;

    Button restart;
    Player* players;
    //Player* players[2];
    //Player player_1;
    //Player player_2;
    Screen screen;
    Ball ball;

    unsigned long autoserve_time;
    unsigned long autoserve_step_time;
    unsigned long waiting_time;
    uint16_t auto_serve_timeout;
    uint8_t active_player;
    bool position_is_allowed;
    void prepare_next_serve();
    bool autoserve_timer();
    bool autoserve_step_timer();
    bool ball_is_in_allowed_position();
    void choose_random_player();
};

#endif
