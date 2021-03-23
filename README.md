# 1D Pong

Pong-like game run on an Arduino MCU and a LED light strip. Inspired by a game seen on 34C3.

## Required Arduino Libraries

* FastLED (v3.1.6): http://fastled.io/
  - In Arduino IDE: Sketch > Include Library > Manage Libraries

## Used Hardware

Hardware build instructons & wiring schemes will be published soon!

* 1x Arduino Pro Mini
* 1x APA102-C LED light strip (1m) with 60 LEDs/m
* 1x 5v power supply (max. 2A)
* BOXEXPERT ABS casings
  - 2x 52x50x35mm IP 65 https://www.boxexpert.de/epages/79711065.sf/de_DE/?ObjectPath=/Shops/79711065/Products/BXPBABS525035-E01
  - 1x 65x50x35mm IP 65 https://www.boxexpert.de/epages/79711065.sf/de_DE/?ObjectPath=/Shops/79711065/Products/BXPBABS655035-E01
* 3x Sanwa OBSN-30 pushbutton 

## Schematic

![Schematic](/schematic/schematic.png?raw=true "Schematic")

The wiring is pretty simple.

All electronics are powered via the same 5V power supply.
Make sure to use a supply that can deliver 2A.

There are three push buttons that pull the pin to high when beeing pressed.
Each button is connected to ground via a pull down resistor.

The input pins of the LED strip are connected to the SPI interface of the arduino.
CI (clock in) is connected to SCK and DI (data in) is connected to MOSI.
The power lines are directly connected to the power source.

## Features
* Game starts immediately after a few seconds
  - You might not need a reset button, if you're willing to switch power off and on.
* During first run:
  - Press Player 1 button to enter low brightness mode for darker environments (late at night, living room, bar/club)
  - Press Player 2 button to enable high speed mode. Every game starts with increased initial speed.

## Feature Requests / Ideas from "Lange nacht der Computerspiele / HTWK Leipzig"

* Allow hits one off (+-1 outside of hit box)
* Feature to charge and release speedup by keep pressing and releasing button
* If one player is close to dead, allow some kind of power move to come back.
* Some feature to gain lifes.