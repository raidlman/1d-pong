// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include <FastLED.h>
#include "Button.h"

class Player {
  public:
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

#endif
