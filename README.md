# 1D Pong

Pong-like game run on an Arduino MCU and a LED light strip. Inspired by a game seen on 34C3.

## Gameplay
Two players at each end of the strip send the ball back and forth by pressing their player button. Each player has an area of several LED's at each end of the strip. The ball is represented by a single white LED and can only be sent to the opposing player, when it hit within ones own area.
The base speed of the ball accelerates whenever the ball is hit by a player.
A goal is attributed once the ball is behind a player's area, which means behind the end of the LED strip.
The game is over once a player scores 8 goals.
Player 1 is represented by 8 green LED's, nearest to the LED connector socket. Player 2 is represented by 8 blue LED's, farther from LED connector socket.
Pro Tip for venturesome players: Hit the ball closer to your own goal to send it back to your opponent with much higher speed.

After 30 seconds without activity the LED strip shows some colorful animations until the next game is being started.

## Required Arduino Libraries

* FastLED (tested with v3.1.6 and 3.4.0): http://fastled.io/
  - In Arduino IDE: Sketch > Include Library > Manage Libraries

## Used Hardware

Hardware build instructons & wiring schemes will be published soon!

* 1x Arduino Pro Mini
  - Adafruit Arduino Pro Mini 5V 16 MHz works, too, including USB power and data support. Separate power supply is not needed in that case. Separate FTDI programmer is not needed, too. The strip can be bus powered straight from the 'bus' pin, which supports 700 mA. This is enough to drive 60 LED's at 80% brightness.
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
Without the resistor each pin would be touch sensitive. Then the pin registers as being pressed, when any cable is attached to it or any finger or metal object touches it. For testing the pins in general, this is a quite useful behaviour.

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