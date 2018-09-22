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

// 1dpong.ino
#include "Pong.h"

// Player settings
const uint8_t LIFES = 8;
const uint16_t BUTTON_LOCK_TIME = 1000;
const uint16_t RESTART_LOCK_TIME = 1000;

// FastLED settings
const uint8_t NUM_LEDS = 100;
const double STRIPE_LENGTH = 1.66;
//const EOrder LED_COLOR_ORDER = BGR;
//const ESPIChipsets LED_TYPE = APA102;
const uint8_t BRIGHTNESS = 64; //max. 255

// Digital pins settings
const uint8_t RESTART_PIN = 2;
const uint8_t PLAYER1_PIN = 3;
const uint8_t PLAYER2_PIN = 4;

// Random settings
const uint8_t RANDOM_SEED_PIN = 4;

Pong pong(PLAYER1_PIN, PLAYER2_PIN, LIFES, BUTTON_LOCK_TIME,
  NUM_LEDS, STRIPE_LENGTH, BRIGHTNESS,
  RESTART_PIN, RESTART_LOCK_TIME, RANDOM_SEED_PIN);

void setup() {
  Serial.begin( 9600 );
  Serial.println("Starting Pong!");
}

void loop() {
  pong.game_logic();
}

