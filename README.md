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

## Feature Requests / Ideas from "Lange nacht der Computerspiele / HTWK Leipzig"

* Allow hits one off (+-1 outside of hit box)
* Feature to charge and release speedup by keep pressing and releasing button
* If one player is close to dead, allow some kind of power move to come back.
* Some feature to gain lifes.