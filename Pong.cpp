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

// Pong.cpp
#include "Pong.h"

Pong::Pong(uint8_t player_1_pin, uint8_t player_2_pin, uint8_t lifes, uint16_t button_lock_time,
      uint8_t num_leds, double stripe_length, uint8_t brightness,
      uint8_t restart_pin, uint16_t restart_lock_time, uint8_t random_seed_pin)
      : player_1(lifes, 0, lifes-1, player_1_pin, button_lock_time, CRGB::Green, CRGB::Red),
        player_2(lifes, num_leds-lifes, num_leds-1, player_2_pin, button_lock_time, CRGB::Blue, CRGB::Red),
        screen(num_leds, brightness),
        restart(restart_pin, restart_lock_time),
        ball(0, 0, num_leds-1, 0.2, 1)
{
	players[0] = &player_1;
	players[1] = &player_2;
  state = WAITING;
  auto_serve_timeout = 2000;
  position_is_allowed = false;
  waiting_time = millis();
  isFirstRun = true;
  randomSeed(analogRead(random_seed_pin));
}

void Pong::prepare_next_serve() {
  ball.reverse_direction();
  ball.reset_speedup();
  autoserve_time = millis();
  autoserve_step_time = millis();
  state = SERVE;
}

void Pong::choose_random_player() {
	// randomly select active player to serve the first ball
	active_player = random(0,2);
	ball.set_position((active_player) ? players[0]->hitbox_min -1 : players[1]->hitbox_max +1);
	ball.set_direction((active_player) ? 1 : -1);
}

bool Pong::autoserve_timer() {
	return (millis() - autoserve_time <= auto_serve_timeout);
}

bool Pong::autoserve_step_timer() {
	return (millis() - autoserve_step_time >= (2000/8));
}

bool Pong::ball_is_in_allowed_position() {
	return (ball.get_position() < player_1.get_autoserve_position() || ball.get_position() > player_2.get_autoserve_position());
}

void Pong::game_logic() {
	if (restart.is_pressed()) {
		screen.clear(ball);
    waiting_time = millis();
    state = WAITING;
	}
  switch(state) {
    case WAITING:
      screen.show_score(player_1, player_2);
      if (restart.is_pressed() || (isFirstRun && (millis() - waiting_time >= 5000))) {
        choose_random_player();

        player_1.reset_lifes();
        player_2.reset_lifes();
        screen.reset(player_1, player_2);

        if (isFirstRun) {
          isFirstRun = false;
        }

        state = SERVE;
      }
      if (millis() - waiting_time >= 30000) {
        state = IDLE;
      }
      break;
    case IDLE:
      screen.show_color_palette();
      if (restart.is_pressed()) {
        screen.reset(player_1, player_2);
        waiting_time = millis();
        state = WAITING;  
      }
      break;
    case PLAYING:
  		if (ball.timer()) {
      	ball.advance();
      	screen.draw(player_1, player_2, ball);
      }

  		if (ball.get_position() < player_1.get_off_position()) {
  			if ( player_1.lose_life() == 0 ) {
          screen.reset(player_1, player_2);
          waiting_time = millis();
  				state = WAITING;
  				break;
  			}
  			active_player = 0;
  			screen.show_score(player_1, player_2);
  			prepare_next_serve();
        break;
  		}

  		if (ball.get_position() > player_2.get_off_position()) {
  			if ( player_2.lose_life() == 0 ) {
          screen.reset(player_1, player_2);
          waiting_time = millis();
  				state = WAITING;
  				break;
  			}
  			active_player = 1;
  			screen.show_score(player_1, player_2);
        prepare_next_serve();
        break;
  		}

  		for (uint8_t i=0; i<2; i++) {
  			if (players[i]->button.is_pressed() && ball.is_inside_hitbox(*players[i])) {
  				active_player = i;
        	ball.hit();
        	ball.calc_speedup(*players[i]);
      	}
  		}
      break;
    case SERVE:
    	// as long as auto_serve_timeout isn't reached, advance ball and calculate speedup for current position
      if ( autoserve_timer() ) {
        if ( ball_is_in_allowed_position() && autoserve_step_timer()) {
        	position_is_allowed = true;
          ball.advance();
          ball.calc_speedup(*players[active_player]);
          autoserve_step_time = millis();
        }
      } else {
        ball.reset_speedup();
        // reset flag
        position_is_allowed = false;
        state = PLAYING;
      }
      // Wait at least one loop for ball to come back in the court ()
      if (players[active_player]->button.is_pressed() && position_is_allowed) {
        // reset flag
        position_is_allowed = false;
        state = PLAYING;
      }
      break;
  }
}
