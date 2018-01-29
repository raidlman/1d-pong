/*
 * 1D Pong
 */

#include <FastLED.h>

// FastLED settings
#define NUM_LEDS 60 // max. 256
#define STRIPE_LENGTH 1.0 // LED length in m
#define LED_COLOR_ORDER BGR
#define LED_TYPE APA102
#define BRIGHTNESS 64
#define MAX_BRIGHTNESS 255

// Digital pins settings
#define RESTART_PIN 7
#define PLAYER1_PIN 8
#define PLAYER2_PIN 9

// Global variables
CRGB leds[NUM_LEDS];

class Button {
  enum ButtonState {
      BUTTON_RELEASED = 0,
      BUTTON_PRESSED
    };
  
  private:
    ButtonState current_state, last_state;
    uint8_t pin;
    unsigned long timer;

    void update_state(){
      last_state = current_state;
      if ( digitalRead(pin) == LOW ) {
        current_state = BUTTON_RELEASED;
      } else {
        current_state = BUTTON_PRESSED;
      }
    }

  public:
    uint8_t set_pin (uint8_t p) {
      pin = p;
      pinMode(p, INPUT);
      return p;
    }
    bool is_pressed() {
      update_state();
      if ( current_state == BUTTON_PRESSED ) {
        return true;
      }
      return false;
    }
};

struct Player {
  Button button;  
};

Player player_1;
Player player_2;
Button restart;

void setup() {
  player_1.button.set_pin(PLAYER1_PIN);
  player_2.button.set_pin(PLAYER2_PIN);
  restart.set_pin(RESTART_PIN);

  Serial.begin( 9600 );
}

void loop() {
  if (player_1.button.is_pressed()) {
    Serial.println("Button P1 pressed!");
  }
  if (player_2.button.is_pressed()) {
    Serial.println("Button P2 pressed!");
  }
  if (restart.is_pressed()) {
    Serial.println("Button Restart pressed!");
  }
}
