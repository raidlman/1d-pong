/*
 * 1D Pong
 */

#include <FastLED.h>
#include "Button.h"

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



struct Player {
  uint8_t lifes = 8;
  uint8_t hitbox_min;
  uint8_t hitbox_max;
  bool serve;
  unsigned long time = 0;
  unsigned long serve_time = 3000;
  CRGB lifes_color;
  CRGB lost_lifes_color;
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

    void reverse_direction() {
      direction *= -1;
    }

    void increase_speed() {
      speed *= 1.05;
    }
  
    void init(int8_t p, double s, int8_t d) {
      position = p;
      speed = s;
      direction = d;
    }
    
  public:
    Ball() {
      init(0,0.2,1);
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

    void hit() {
      reverse_direction();
      increase_speed();
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

    void draw_player_score(Player p){
      for (uint8_t i=p.hitbox_min; i<=p.hitbox_max; i++) {
        if ( i < 29 ) {
          if ( i < (8 - p.lifes)) {
            leds[i] = p.lost_lifes_color;
          } else {
            leds[i] = p.lifes_color;
          }
        } else {
          if ( i <= ( 51 + p.lifes )) {
            leds[i] = p.lifes_color;
          } else {
            leds[i] = p.lost_lifes_color;
          }
        }
      }
    }
    
  public:
    Screen() {
      init();
    }

    void show_score(Player &p1, Player &p2) {
      draw_player_score(p1);
      draw_player_score(p2);
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
Screen screen;
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
