// Screen.h
#ifndef SCREEN_H
#define SCREEN_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <FastLED.h>
#include "Ball.h"
#include "Player.h"

class Screen {
  private:
    uint8_t num_leds;
    CRGB *leds;
    //ESPIChipsets led_type;
    //EOrder led_color_order;
    uint8_t brightness;

    void init();
    void draw_player_score(Player p);
    
  public:
    Screen(uint8_t bright, uint8_t num);

    void show_score(Player &p1, Player &p2);
    void advance_ball(Ball &b, Player &p1, Player &p2);
};

#endif
