#include "Pong.h"

Pong::Pong(uint8_t player_1_pin, uint8_t player_2_pin, uint8_t lifes, uint16_t button_lock_time,
      uint8_t num_leds, double stripe_length, uint8_t brightness,
      uint8_t restart_pin, uint16_t restart_lock_time)
      : player_1(lifes, 0, 7, player_1_pin, button_lock_time, CRGB::Green, CRGB::Black),
        player_2(lifes, num_leds-8, num_leds-1, player_2_pin, button_lock_time, CRGB::Blue, CRGB::Black),
        screen(num_leds, brightness),
        restart(restart_pin, restart_lock_time)
{

}

void Pong::game_logic() {

    if (ball.timer()) {
      screen.advance_ball(ball, player_1, player_2);
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
