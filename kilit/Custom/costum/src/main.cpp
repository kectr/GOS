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

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
uint8_t incomingByte;
uint8_t red, green, blue;
int16_t i, j;

void setup()
{
  Serial.begin(115200);
  matrix.begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    blue = bitRead(incomingByte, 0) ? 1 : 0;
    green = bitRead(incomingByte, 1) ? 1 : 0;
    red = bitRead(incomingByte, 2) ? 1 : 0;
    matrix.drawPixel(i, j, matrix.Color333(red, green, blue));
    i++;
    if(i>31){
      i = 0;
      j++;
    }
    if(j>15){
      j = 0;
    }
  }  
}
