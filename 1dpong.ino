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
  uint8_t lifes;
  uint8_t hitbox_min;
  uint8_t hitbox_max;
  CRGB color;
  Button button;
};

class Ball {
  private:
  
    int8_t position;
    double speed;
    int8_t direction;
    unsigned long time;

    uint8_t distance_to_field_boundary (Player &player) {
      return abs(player.hitbox_min - position);
    }
    
    // convert speed (in m/s) to timer delay
    uint16_t speed_to_timer() {
      double s = speed; // + ball.speedup;
      return (uint16_t)(STRIPE_LENGTH*1000 / ((NUM_LEDS)*speed));
    }
    
  public:
    void init(int8_t p, double s, int8_t d) {
      position = p;
      speed = s;
      direction = d;
    }
  
    bool is_inside_hitbox(Player &player) {
      if ( player.hitbox_min <= position && position <= player.hitbox_max ) {
        return true;
      }
      return false;
    }
    
    bool timer() {
      if ( millis() - time >= speed_to_timer() ) {
        //Serial.println(time);
        //Serial.println(millis() - time);
        time = millis();
        return true;
      }
      return false;
    }

    int8_t get_position() {
      return position;
    }
    
    void set_position(int8_t p) {
      position = p;
    }

    int8_t get_direction() {
      return direction;
    }

    void reverse_direction() {
      direction *= -1;
    }
    /*
    void advance() {
      position += direction;
    }*/
};

class Screen {
  private:
    // Global variables
    CRGB leds[NUM_LEDS-1];

    void draw_player_score(Player p){
      for (uint8_t i=p.hitbox_min; i<=p.hitbox_max; i++) {
        leds[i] = p.color;
      }
    }
    
  public:
  
    void init() {
      // set chipset type, color order of LEDs and number of LEDs on stripe
      FastLED.addLeds<LED_TYPE, LED_COLOR_ORDER>(leds, NUM_LEDS);
      
      // set global brightness
      FastLED.setBrightness( BRIGHTNESS );
      
      // turn off all LEDs
      for (uint8_t i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB::Black;
      }
       
      FastLED.show();
    }
    
    void advance_ball(Ball &b, Player &p1, Player &p2) {
      leds[b.get_position()] = CRGB::Black;
      
      draw_player_score(p1);
      draw_player_score(p2);
      
      b.set_position(b.get_position() + b.get_direction());
      leds[b.get_position()] = CRGB::White;
      FastLED.show();
    }
};

Player player_1;
Player player_2;
Button restart;
Screen screen;
Ball ball;

void setup() {
  player_1.button.set_pin(PLAYER1_PIN);
  player_2.button.set_pin(PLAYER2_PIN);
  player_1.hitbox_min=0;
  player_1.hitbox_max=7;
  player_2.hitbox_min=NUM_LEDS-9;
  player_2.hitbox_max=NUM_LEDS-1;
  player_1.color = CRGB::Green;
  player_2.color = CRGB::Blue;
  restart.set_pin(RESTART_PIN);
  screen.init();
  ball.init(0,0.2,1);

//  Serial.begin( 9600 );
}

void loop() {
/*
  if (player_1.button.is_pressed()) {
    Serial.println("Button P1 pressed!");
  }
  if (player_2.button.is_pressed()) {
    Serial.println("Button P2 pressed!");
  }
  if (restart.is_pressed()) {
    Serial.println("Button Restart pressed!");
  }
*/
  if (ball.timer()) {
    screen.advance_ball(ball, player_1, player_2);
  }
}
