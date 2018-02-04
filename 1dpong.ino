/*
 * 1D Pong
 */

#include <FastLED.h>
#include "Button.h"
#include "Ball.h"
#include "Player.h"
#include "Screen.h"

// Player settings
const uint8_t LIFES = 8;
const uint16_t BUTTON_LOCK_TIME = 1000;

// FastLED settings
const uint8_t NUM_LEDS = 60;
const double STRIPE_LENGTH = 1.0;
const EOrder LED_COLOR_ORDER = BGR;
const ESPIChipsets LED_TYPE = APA102;
const uint8_t BRIGHTNESS = 64; //max. 255

// Digital pins settings
const uint8_t RESTART_PIN = 7;
const uint8_t PLAYER1_PIN = 8;
const uint8_t PLAYER2_PIN = 9;

enum State {
  IDLE = 0,
  DEMO,
  PLAYING,
  SERVE,
  WIN
};


Player player_1(LIFES, 0, 7, PLAYER1_PIN, BUTTON_LOCK_TIME, CRGB::Green, CRGB::Black);
Player player_2(LIFES, NUM_LEDS-8, NUM_LEDS-1, PLAYER2_PIN, BUTTON_LOCK_TIME, CRGB::Blue, CRGB::Black);

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

  restart.set_pin(RESTART_PIN);
  restart.set_lock_time(1000);

  Serial.begin( 9600 );
  Serial.println("Starting Pong!");

}

void loop() {
  game_logic();
}

