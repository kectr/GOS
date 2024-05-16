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

#define player1up 11
#define player1down 12
#define player2up 13
#define player2down 19 // A5

#define timeinterval 150

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

int8_t player1Vel = 0;
int8_t player2Vel = 0;
int8_t player1Pos = 10;
int8_t player2Pos = 10;

int8_t ballPosx = 15;
int8_t ballPosy = 7;
int8_t ballVelx = 1;
int8_t ballVely = 1;

bool player1Win = false;
bool player2Win = false;

int lasttime = 0;
int deltat = 0;

void updatePos();
void updateVel();

void setup()
{
  matrix.begin();
  pinMode(player1down, INPUT);
  pinMode(player2down, INPUT);
  pinMode(player1up, INPUT);
  pinMode(player2up, INPUT);
}

void loop()
{
  deltat = millis() - lasttime;
  // updateVel();
  if (deltat > timeinterval)
  {
    lasttime = millis();
    // updateVel();
    updatePos();
    if (player1Win)
    {
      matrix.drawLine(28, player2Pos, 28, player2Pos + 5, matrix.Color333(1, 0, 0));
      matrix.setCursor(10, 1);
      matrix.setTextColor(matrix.Color333(1, 1, 0));
      matrix.setTextSize(1);
      matrix.print("P1");
      matrix.setCursor(8, 9);
      matrix.print("WIN");
      delay(1000);
      player1Vel = 0;
      player2Vel = 0;
      player1Pos = 5;
      player2Pos = 5;
      player1Win = false;
      player2Win = false;
      ballPosx = 15;
      ballPosy = 7;
      ballVelx = 1;
      ballVely = 1;
    }
    else if (player2Win)
    {
      matrix.drawLine(3, player1Pos, 3, player1Pos + 5, matrix.Color333(1, 0, 0));
      matrix.setCursor(10, 1);
      matrix.setTextColor(matrix.Color333(1, 1, 0));
      matrix.setTextSize(1);
      matrix.print("P2");
      matrix.setCursor(8, 9);
      matrix.print("WIN");
      delay(1000);
      player1Vel = 0;
      player2Vel = 0;
      player1Pos = 5;
      player2Pos = 5;
      player1Win = false;
      player2Win = false;
      ballPosx = 15;
      ballPosy = 7;
      ballVelx = 1;
      ballVely = 1;
    }
    else
    {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      matrix.drawLine(3, player1Pos, 3, player1Pos + 5, matrix.Color333(1, 1, 1));
      matrix.drawLine(28, player2Pos, 28, player2Pos + 5, matrix.Color333(1, 1, 1));
      matrix.drawPixel(ballPosx, ballPosy, matrix.Color333(1, 1, 0));
    }
  }
  else
  {
  }
}


void updatePos()
{
  player1Pos += player1Vel;
  player2Pos += player2Vel;

  ballPosx += ballVelx;
  ballPosy += ballVely;

  if (ballPosx > 31)
  {
    ballPosx = 31;
    ballVelx = -ballVelx;
    player1Win = true;
  }

  if (ballPosx < 0)
  {
    ballPosx = 0;
    ballVelx = -ballVelx;
    player2Win = true;
  }

  if (ballPosy > 15)
  {
    ballPosy = 15;
    ballVely = -ballVely;
  }

  if (ballPosy < 0)
  {
    ballPosy = 0;
    ballVely = -ballVely;
  }

  if (player1Pos < 0)
  {
    player1Pos = 0;
  }
  else if (player1Pos > 10)
  {
    player1Pos = 10;
  }
  if (player2Pos < 0)
  {
    player2Pos = 0;
  }
  else if (player2Pos > 10)
  {
    player2Pos = 10;
  }

  if (ballPosx == 3 && (ballPosy - player1Pos) > 0 && (ballPosy - player1Pos) <= 6)
  {
    ballPosx = 4;
    ballVelx = -ballVelx;
  }

  if (ballPosx == 28 && (ballPosy - player2Pos) > 0 && (ballPosy - player2Pos) <= 6)
  {
    ballPosx = 27;
    ballVelx = -ballVelx;
  }
}

void updateVel()
{
  if (digitalRead(player1down) == HIGH)
  {
    player1Vel = 1;
  }
  else if (digitalRead(player1up) == HIGH)
  {
    player1Vel = -1;
  }
  else
  {
    player1Vel = 0;
  }
  if (digitalRead(player2down) == HIGH)
  {
    player2Vel = 1;
  }
  else if (digitalRead(player2up) == HIGH)
  {
    player2Vel = -1;
  }
  else
  {
    player2Vel = 0;
  }
}
