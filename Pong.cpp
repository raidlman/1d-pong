#include "Pong.h"

Pong::Pong(uint8_t player_1_pin, uint8_t player_2_pin, uint8_t lifes, uint16_t button_lock_time,
      uint8_t num_leds, double stripe_length, uint8_t brightness,
      uint8_t restart_pin, uint16_t restart_lock_time)
      : player_1(lifes, 0, lifes-1, player_1_pin, button_lock_time, CRGB::Green, CRGB::Red),
        player_2(lifes, num_leds-lifes, num_leds-1, player_2_pin, button_lock_time, CRGB::Blue, CRGB::Red),
        screen(num_leds, brightness),
        restart(restart_pin, restart_lock_time),
        ball(0, 0, num_leds-1, 0.2, 1)
{
	players[0] = &player_1;
	players[1] = &player_2;
  state = IDLE;
  auto_serve_timeout = 2000;
  ball_is_in_legit_position = false;
}

void Pong::game_logic() {
  switch(state) {
    case IDLE:
      screen.show_score(player_1, player_2);
      if (restart.is_pressed()) {
        state = PLAYING;  
      }
      break;
    case PLAYING:
  		if (ball.timer()) {
      	ball.advance();
      	screen.draw(player_1, player_2, ball);
      }
  		if (ball.get_position() < player_1.get_off_position()) {
  			player_1.lose_life();
  			active_player = 0;
  			screen.show_score(player_1, player_2);
        ball.reverse_direction();
        ball.reset_speedup();
        state = SERVE;
        time = millis();
        time2 = millis();
        break;
  		}
  		if (ball.get_position() > player_2.get_off_position()) {
  			player_2.lose_life();
  			active_player = 1;
  			screen.show_score(player_1, player_2);
        ball.reverse_direction();
        ball.reset_speedup();
        state = SERVE;
        time = millis();
        time2 = millis();
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
      if ( millis() - time <= auto_serve_timeout ) {
        if ((ball.get_position() < player_1.get_autoserve_position() || ball.get_position() > player_2.get_autoserve_position()) && millis() - time2 >= (2000/8)) {
        	ball_is_in_legit_position = true;
          ball.advance();
          ball.calc_speedup(*players[active_player]);
          time2 = millis();
        }
      } else {
        ball.reset_speedup();
        // reset flag
        ball_is_in_legit_position = false;
        state = PLAYING;
      }
      // Wait at least one loop for ball to come back in the court ()
      if (players[active_player]->button.is_pressed() && ball_is_in_legit_position) {
        // reset flag
        ball_is_in_legit_position = false;
        state = PLAYING;
      }
      break;
  }
}
