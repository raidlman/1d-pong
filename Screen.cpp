/*
 * 1D Pong - Pong-like game run on an Arduino MCU
 * Copyright (C) 2018  Stephan Riedel - raidlman@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Screen.cpp
#include "Screen.h"
#include <FastLED.h>


void Screen::init() {
  // set chipset type, color order of LEDs and number of LEDs on stripe
  //FastLED.addLeds<led_type, led_color_order>(leds, num_leds);
  FastLED.addLeds<APA102, BGR>(leds, num_leds).setCorrection( TypicalLEDStrip );
  
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
    if ( i < (num_leds/2 - 1) ) {
      if ( i < ( p.initial_lifes - p.lifes )) {
        leds[i] = p.lost_lifes_color;
      } else {
        leds[i] = p.lifes_color;
      }
    } else {
      if ( i < ( num_leds - p.initial_lifes + p.lifes )) {
        leds[i] = p.lifes_color;
      } else {
        leds[i] = p.lost_lifes_color;
      }
    }
  }
}

Screen::Screen(uint8_t num_leds, uint8_t brightness) : leds(new CRGB[num_leds]) {
  //led_type = type;
  //led_color_order = order;
  this->brightness = brightness;
  this->num_leds = num_leds;
  color_pallette_updates_per_second = 100;

  init();
}

void Screen::show_score(Player &p1, Player &p2) {
  draw_player_score(p1);
  draw_player_score(p2);

  FastLED.show();
}

void Screen::advance_ball(Ball &b, Player &p1, Player &p2) {
  leds[b.get_position()] = CRGB::Black;
  
  b.set_position(b.get_position() + b.get_direction());
  leds[b.get_position()] = CRGB::White;
  
  FastLED.show();
}

void Screen::clear_led(uint8_t num) {
  leds[num] = CRGB::Black;
}

void Screen::clear_all_leds() {
  for (uint8_t i=0; i<num_leds; i++){
    leds[i] = CRGB::Black;
  }
}

void Screen::clear(Ball &ball) {
  clear_led(ball.get_position());
}

void Screen::reset(Player &p1, Player &p2) {
  clear_all_leds();
  show_score(p1, p2);
}

void Screen::draw_ball(uint8_t num) {
  leds[num] = CRGB::White;
}

void Screen::draw(Player &player_1, Player &player_2, Ball &ball) {
  clear_led(ball.get_previous_position());
  draw_player_score(player_1);
  draw_player_score(player_2);
  draw_ball(ball.get_position());
  FastLED.show();
}

void Screen::show_color_palette() {
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / color_pallette_updates_per_second);
}


void Screen::FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < num_leds; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void Screen::ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

void Screen::SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void Screen::SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

void Screen::SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};