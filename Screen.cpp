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

// Screen.cpp
#include "Screen.h"
#include <FastLED.h>

void Screen::init() {
  // set chipset type, color order of LEDs and number of LEDs on stripe
  //FastLED.addLeds<led_type, led_color_order>(leds, num_leds);
  FastLED.addLeds<APA102, BGR>(leds, num_leds).setCorrection( TypicalLEDStrip );
  
  // set global brightness
  FastLED.setBrightness( brightness );
  
  // turn off all LEDs
  for (uint8_t i=0; i<num_leds; i++){
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
}

void Screen::draw_player_score(Player p){
  for (uint8_t i=p.hitbox_min; i<=p.hitbox_max; i++) {
    if ( i < (num_leds/2 - 1) ) {
      if ( i < ( p.initial_lifes - p.lifes )) {
        leds[i] = p.lost_lifes_color;
      } else {
        leds[i] = p.lifes_color;
      }
    } else {
      if ( i < ( num_leds - p.initial_lifes + p.lifes )) {
        leds[i] = p.lifes_color;
      } else {
        leds[i] = p.lost_lifes_color;
      }
    }
  }
}

Screen::Screen(uint8_t num_leds, uint8_t brightness) : leds(new CRGB[num_leds]) {
  //led_type = type;
  //led_color_order = order;
  this->brightness = brightness;
  this->num_leds = num_leds;

  init();
}

void Screen::show_score(Player &p1, Player &p2) {
  draw_player_score(p1);
  draw_player_score(p2);

  FastLED.show();
}

void Screen::advance_ball(Ball &b, Player &p1, Player &p2) {
  leds[b.get_position()] = CRGB::Black;
  
  
  
  b.set_position(b.get_position() + b.get_direction());
  leds[b.get_position()] = CRGB::White;
  
  FastLED.show();
}

void Screen::clear_led(uint8_t num) {
  leds[num] = CRGB::Black;
}

void Screen::clear(Ball &ball) {
  clear_led(ball.get_position());
}

void Screen::draw_ball(uint8_t num) {
  leds[num] = CRGB::White;
}

void Screen::draw(Player &player_1, Player &player_2, Ball &ball) {
  clear_led(ball.get_previous_position());
  draw_player_score(player_1);
  draw_player_score(player_2);
  draw_ball(ball.get_position());
  FastLED.show();
}
