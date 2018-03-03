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
    void clear_led(uint8_t num);
    void draw_ball(uint8_t num);
    
  public:
    Screen(uint8_t num_leds, uint8_t brightness);

    void show_score(Player &p1, Player &p2);
    void advance_ball(Ball &b, Player &p1, Player &p2);
    void draw(Player &player_1, Player &player_2, Ball &ball);
    void clear(Ball &ball);
};

#endif
