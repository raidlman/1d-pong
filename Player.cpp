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

// Player.cpp
#include "Player.h"

Player::Player() {

}

Player::Player(uint8_t lifes, uint8_t hitbox_min, uint8_t hitbox_max, uint8_t input_pin, uint16_t lock_time, CRGB lifes_color, CRGB lost_lifes_color) {
	this->lifes = lifes;
	this->hitbox_min = hitbox_min;
	this->hitbox_max = hitbox_max;
	this->lifes_color = lifes_color;
  this->lost_lifes_color = lost_lifes_color;
  initial_lifes = lifes;
  button.set_pin(input_pin);
  button.set_lock_time(lock_time);
}

uint8_t Player::lose_life() {
  lifes -= 1;
  return lifes;
}

uint8_t Player::get_off_position() {
	return (hitbox_min) ? hitbox_max : hitbox_min;
}

uint8_t Player::get_autoserve_position() {
	return (hitbox_min) ? hitbox_min : hitbox_max;
}

void Player::reset_lifes() {
	lifes = initial_lifes;
}