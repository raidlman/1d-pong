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

// Ball.cpp
#include "Ball.h"

uint8_t Ball::distance_to_field_boundary (Player &player) {
  if ( position > 29 ) {
    return position - player.hitbox_min;
  } else {
    return player.hitbox_max - position;
  }
}

// convert speed (in m/s) to timer delay
uint16_t Ball::speed_to_timer() {
  double s = speed + speedup;
  //return (uint16_t)((STRIPE_LENGTH*1000.0) / (NUM_LEDS*s));
  return (uint16_t)((1.0*1000.0) / (60*s));
}

void Ball::reverse_direction() {
  direction *= -1;
}

void Ball::increase_speed() {
  speed *= 1.05;
}

Ball::Ball(int8_t position, uint8_t min_position, uint8_t max_position, double speed, int8_t direction) {
//  init(0,0.2,1);
  this->position = position;
  this->min_position = min_position;
  this->max_position = max_position;
  this->speed = speed;
  this->initial_speed = speed;
  this->direction = direction;
  speedup = 0.0;
}

bool Ball::is_inside_hitbox(Player &player) {
  if ( player.hitbox_min <= position && position <= player.hitbox_max ) {
    return true;
  }
  return false;
}

bool Ball::timer() {
  if ( millis() - time >= speed_to_timer() ) {
    time = millis();
    return true;
  }
  return false;
}

int8_t Ball::get_position() {
  return position;
}

int8_t Ball::get_previous_position() {
  return previous_position;
}

void Ball::set_position(int8_t position) {
  this->position = position;
}

void Ball::set_direction(uint8_t direction) {
  this->direction = direction;
}

int8_t Ball::get_direction() {
  return direction;
}

void Ball::hit() {
  reverse_direction();
  increase_speed();
}

void Ball::increase_initial_speed() {
  this->initial_speed = 0.6;
}

void Ball::calc_speedup(Player &player) {
  speedup = distance_to_field_boundary(player)/10.0;
}

void Ball::advance() {
  previous_position = position;
  position += direction;
}

void Ball::serve(Player player) {
  
}

void Ball::reset_speedup() {
  speed = initial_speed;
  speedup = 0.0;
}
