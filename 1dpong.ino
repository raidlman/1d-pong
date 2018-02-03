/*
 * 1D Pong
 */

#include <FastLED.h>
#include "Button.h"
#include "Ball.h"
#include "Player.h"
#include "Screen.h"

// FastLED settings
const uint8_t NUM_LEDS=60;
const double STRIPE_LENGTH=1.0;
const EOrder LED_COLOR_ORDER=BGR;
const ESPIChipsets LED_TYPE=APA102;
const uint8_t BRIGHTNESS=64; //max. 255

// Digital pins settings
const uint8_t RESTART_PIN=7;
const uint8_t PLAYER1_PIN=8;
const uint8_t PLAYER2_PIN=9;

enum State {
  IDLE = 0,
  DEMO,
  PLAYING,
  SERVE,
  WIN
};

Player player_1;
Player player_2;
Button restart;
Screen screen(BRIGHTNESS, NUM_LEDS);
Ball ball;
State state = IDLE;

void game_logic() {
  switch(state) {
    case IDLE:
      if (restart.is_pressed()) {
        state = SERVE;
        player_1.serve_time = millis();
      }
      break;
    case DEMO:
      break;
    case SERVE:
      screen.show_score(player_1, player_2);
      if ( millis() - player_1.time >= player_1.serve_time ) {
        state = PLAYING;
      }
      break;
    case PLAYING:
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
      break;
    case WIN: break;
    default: break;
  }
}

void setup() {
  player_1.button.set_pin(PLAYER1_PIN);
  player_2.button.set_pin(PLAYER2_PIN);
  player_1.button.set_lock_time(1000);
  player_2.button.set_lock_time(1000);
  
  player_1.hitbox_min=0;
  player_1.hitbox_max=7;
  player_2.hitbox_min=NUM_LEDS-8;
  player_2.hitbox_max=NUM_LEDS-1;
  
  player_1.lifes_color = CRGB::Green;
  player_1.lost_lifes_color = CRGB::Black;
  player_2.lifes_color = CRGB::Blue;
  player_2.lost_lifes_color = CRGB::Black;

  player_1.serve = true;
  player_1.serve = false;
  
  restart.set_pin(RESTART_PIN);
  restart.set_lock_time(1000);

  Serial.begin( 9600 );
  Serial.println("Starting Pong!");

}

void loop() {
  game_logic();
}

