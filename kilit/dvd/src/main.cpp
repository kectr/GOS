// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>
#include <Arduino.h>
// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK 8 // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
// #define CLK A4 // USE THIS ON METRO M4 (not M0)
// #define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2

#define timeinterval 150

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int8_t ballPosx = 15;
int8_t ballPosy = 7;
int8_t ballVelx = 1;
int8_t ballVely = 1;
uint8_t color = 1;

int lasttime = 0;
int deltat = 0;

bool updatePos();


void setup()
{
  matrix.begin();
}



void loop()
{
  deltat = millis() - lasttime;
  if (deltat > timeinterval)
  {
    lasttime = millis();
    if(updatePos()){
      color+=1;
      if(color>7){
        color = 1;
      }
    }
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    matrix.drawPixel(ballPosx, ballPosy, matrix.Color333(bitRead(color,2), bitRead(color,1), bitRead(color,0)));
  }
}

bool updatePos()
{
  bool hit = false;
  ballPosx += ballVelx;
  ballPosy += ballVely;

  if (ballPosx > 31)
  {
    ballPosx = 31;
    ballVelx = -ballVelx;
    hit  = true;
  }

  if (ballPosx < 0)
  {
    ballPosx = 0;
    ballVelx = -ballVelx;
    hit  = true;
  }

  if (ballPosy > 15)
  {
    ballPosy = 15;
    ballVely = -ballVely;
    hit  = true;
  }

  if (ballPosy < 0)
  {
    ballPosy = 0;
    ballVely = -ballVely;
    hit  = true;
  }
  return hit;
}