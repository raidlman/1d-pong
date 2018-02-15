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