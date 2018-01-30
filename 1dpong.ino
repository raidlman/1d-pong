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
    ButtonState current_state;
    uint8_t pin;
    bool lock;
    unsigned long time;
    unsigned long lock_time;

    void update_state(){
      if ( digitalRead(pin) == HIGH && millis() - time >= lock_time ) {
          current_state = BUTTON_PRESSED;
          time = millis();
      } else {
        current_state = BUTTON_RELEASED;
      }
    }

  public:
    void set_pin (uint8_t p) {
      pin = p;
      pinMode(p, INPUT);
    }
    void set_lock_time(double t) {
      lock_time = t;
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
  uint8_t boundary;
  CRGB color;
  Button button;
};

class Ball {
  private:
  
    int8_t position;
    double speed;
    double speedup = 0.0;
    int8_t direction;
    unsigned long time;

    uint8_t distance_to_field_boundary (Player &player) {
      if ( position > 29 ) {
        return position - player.hitbox_min;
      } else {
        return player.hitbox_max - position;
      }
    }
    
    // convert speed (in m/s) to timer delay
    uint16_t speed_to_timer() {
      double s = speed + speedup;
      return (uint16_t)(STRIPE_LENGTH*1000 / ((NUM_LEDS)*s));
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

    void calc_speedup(Player p) {
      speedup = distance_to_field_boundary(p)/10.0;
      Serial.println(speedup);
    }
};

class Screen {
  private:
    // Global variables
    CRGB leds[NUM_LEDS];

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

enum class Pong {
  IDLE = 0,
  DEMO,
  PLAY,
  WIN
} pong;

enum class Match {
  SERVE_P1 = 0,
  SERVE_P2
  
} match;

Player player_1;
Player player_2;
Button restart;
Screen screen;
Ball ball;

void setup() {
  player_1.button.set_pin(PLAYER1_PIN);
  player_2.button.set_pin(PLAYER2_PIN);
  player_1.button.set_lock_time(1000);
  player_2.button.set_lock_time(1000);
  player_1.hitbox_min=0;
  player_1.hitbox_max=7;
  player_1.boundary=0;
  player_2.hitbox_min=NUM_LEDS-9;
  player_2.hitbox_max=NUM_LEDS-1;
  player_2.boundary=NUM_LEDS-9;
  player_1.color = CRGB::Green;
  player_2.color = CRGB::Blue;
  restart.set_pin(RESTART_PIN);
  screen.init();
  ball.init(0,0.2,1);

  Serial.begin( 9600 );
  Serial.println("Starting Pong!");
}

void loop() {
  
  if (ball.timer()) {
    screen.advance_ball(ball, player_1, player_2);
  }
  if (player_1.button.is_pressed() && ball.is_inside_hitbox(player_1)) {
    ball.reverse_direction();
    ball.calc_speedup(player_1);
  }
  if (player_2.button.is_pressed() && ball.is_inside_hitbox(player_2)) {
    ball.reverse_direction();
    ball.calc_speedup(player_2);
  }
}
