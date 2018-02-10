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

}

void Pong::game_logic() {
		if (ball.timer()) {
    	ball.advance();
    	screen.draw(player_1, player_2, ball);
    }
		if (ball.get_position() < 0) {
			player_1.lose_life();
			ball.set_position(0);
			ball.reverse_direction();
			ball.reset_speedup();
		}
		if (ball.get_position() > 59) {
			player_2.lose_life();
			ball.set_position(59);
			ball.reverse_direction();
			ball.reset_speedup();
		}
		if (player_1.button.is_pressed() && ball.is_inside_hitbox(player_1)) {
      ball.hit();
      ball.calc_speedup(player_1);
    }
    if (player_2.button.is_pressed() && ball.is_inside_hitbox(player_2)) {
      ball.hit();
      ball.calc_speedup(player_2);
    }
    
}
