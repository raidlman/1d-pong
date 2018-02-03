#include "Screen.h"
#include <FastLED.h>

void Screen::init() {
  // set chipset type, color order of LEDs and number of LEDs on stripe
  //FastLED.addLeds<led_type, led_color_order>(leds, num_leds);
  FastLED.addLeds<APA102, BGR>(leds, num_leds);
  
  // set global brightness
  FastLED.setBrightness( brightness );
  
  // turn off all LEDs
  for (uint8_t i=0; i<num_leds; i++){
    leds[i] = CRGB::Black;
  }
  
  FastLED.show();
}

void Screen::draw_player_score(Player p){
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

Screen::Screen(uint8_t bright, uint8_t num) {
  //led_type = type;
  //led_color_order = order;
  brightness = bright;
  num_leds = num;
  leds = new CRGB[num];

  init();
}

void Screen::show_score(Player &p1, Player &p2) {
  draw_player_score(p1);
  draw_player_score(p2);
  FastLED.show();
}

void Screen::advance_ball(Ball &b, Player &p1, Player &p2) {
  leds[b.get_position()] = CRGB::Black;
  
  draw_player_score(p1);
  draw_player_score(p2);
  
  b.set_position(b.get_position() + b.get_direction());
  leds[b.get_position()] = CRGB::White;
  FastLED.show();
}
