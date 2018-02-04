#include "Player.h"

Player::Player(uint8_t initial_lifes, uint8_t min, uint8_t max, uint8_t input_pin, uint16_t lock_time, CRGB lifes_col, CRGB lost_lifes_col) {
	lifes = initial_lifes;
	hitbox_min = min;
	hitbox_max = max;
	lifes_color = lifes_col;
  lost_lifes_color = lost_lifes_col;
  button.set_pin(input_pin);
  button.set_lock_time(lock_time);
}