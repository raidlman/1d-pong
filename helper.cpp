#include "helper.h"

#include "Player.h"

Player * createPlayers( uint8_t numPlayers, uint8_t lifes, uint8_t numLeds, uint16_t button_lock_time) {
  long unsigned int  playerColors[2] = { CRGB::Green, CRGB::Blue};
  uint8_t playerPins[2] = { 3, 4};

  Player * newPlayers = new Player[ 2];
  newPlayers[0] = Player(lifes, 0, lifes - 1, playerPins[0], button_lock_time, playerColors[0], CRGB::Red);
  newPlayers[1] = Player(lifes, numLeds - lifes, numLeds - 1, playerPins[1], button_lock_time, playerColors[1], CRGB::Red);

  return newPlayers;
}

