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

void Ball::init(int8_t p, double s, int8_t d) {
  position = p;
  speed = s;
  direction = d;
}

Ball::Ball() {
  init(0,0.2,1);
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

void Ball::set_position(int8_t p) {
  position = p;
}

int8_t Ball::get_direction() {
  return direction;
}

void Ball::hit() {
  reverse_direction();
  increase_speed();
}

void Ball::calc_speedup(Player p) {
  speedup = distance_to_field_boundary(p)/10.0;
}

