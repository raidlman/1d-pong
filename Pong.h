// Pong.h
#ifndef PONG_H
#define PONG_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "Button.h"
#include "Ball.h"
#include "Player.h"
#include "Screen.h"

class Pong {
	public:
		Pong(uint8_t player_1_pin, uint8_t player_2_pin, uint8_t lifes, uint16_t button_lock_time,
		  uint8_t num_leds, double stripe_length, uint8_t brightness,
		  uint8_t restart_pin, uint16_t restart_lock_time);

		Button restart;
		Player player_1;
		Player player_2;
		Screen screen;
		Ball ball;

    void game_logic();

	private:
		/*
    enum State {
      IDLE = 0,
      DEMO,
      PLAYING,
      SERVE,
      WIN
    } state = IDLE;
    */
};

#endif
