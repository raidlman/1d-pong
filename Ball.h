// Ball.h
#ifndef BALL_H
#define BALL_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif
#include "Player.h"

class Ball {
  private:
  
    int8_t position;
    double speed;
    double speedup = 0.0;
    int8_t direction;
    unsigned long time;

    uint8_t distance_to_field_boundary (Player &player);
    
    // convert speed (in m/s) to timer delay
    uint16_t speed_to_timer();
    void reverse_direction();
    void increase_speed();
    void init(int8_t position, double speed, int8_t direction);
    
  public:
    Ball();

    bool is_inside_hitbox(Player &player);
    bool timer();
    int8_t get_position();
    void set_position(int8_t p);
    int8_t get_direction();
    void hit();

    void calc_speedup(Player p);
};

#endif
