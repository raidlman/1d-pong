/*
 * 1D Pong
 */

#include "Pong.h"

// Player settings
const uint8_t LIFES = 8;
const uint16_t BUTTON_LOCK_TIME = 1000;
const uint16_t RESTART_LOCK_TIME = 1000;

// FastLED settings
const uint8_t NUM_LEDS = 60;
const double STRIPE_LENGTH = 1.0;
//const EOrder LED_COLOR_ORDER = BGR;
//const ESPIChipsets LED_TYPE = APA102;
const uint8_t BRIGHTNESS = 64; //max. 255

// Digital pins settings
const uint8_t RESTART_PIN = 7;
const uint8_t PLAYER1_PIN = 8;
const uint8_t PLAYER2_PIN = 9;

Pong pong(PLAYER1_PIN, PLAYER2_PIN, LIFES, BUTTON_LOCK_TIME,
  NUM_LEDS, STRIPE_LENGTH, BRIGHTNESS,
  RESTART_PIN, RESTART_LOCK_TIME);

void setup() {
  Serial.begin( 9600 );
  Serial.println("Starting Pong!");
}

void loop() {
  pong.game_logic();
}

