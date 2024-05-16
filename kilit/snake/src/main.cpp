#include <RGBmatrixPanel.h>
#include <Arduino.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

#define CLK 8 // USE THIS ON ADAFRUIT METRO M0, etc.
// #define CLK A4 // USE THIS ON METRO M4 (not M0)
// #define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE 9
#define LAT 10
#define A A0
#define B A1
#define C A2

#define playerright 11
#define playerleft 12

// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void updateVel();

bool snakeMove();

void newApple();

class cordinate
{
public:
  int8_t x;
  int8_t y;
  cordinate();
  cordinate(int8_t x, int8_t y);
  void set(int8_t x, int8_t y);
  void set(cordinate cor);
};

bool isSnake(cordinate cor);

cordinate::cordinate() {}

cordinate::cordinate(int8_t x, int8_t y)
{
  set(x, y);
}

void cordinate::set(int8_t x, int8_t y)
{
  cordinate::x = x;
  cordinate::y = y;
}

void cordinate::set(cordinate cor)
{
  cordinate::x = cor.x;
  cordinate::y = cor.y;
}

cordinate *snake = new cordinate[50];

uint8_t lenght = 2;

cordinate headdirection(1, 0);
cordinate apple(0, 0);

int lasttime = 0;
int deltat = 0;

void setup()
{
  matrix.begin();
  pinMode(playerright, INPUT);
  pinMode(playerleft, INPUT);
  snake[0].set(15, 7);
  snake[1].set(14, 7);
  newApple();
}

int timeinterval = 100;

void loop()
{
  //updateVel();
  deltat = millis() - lasttime;
  if (deltat > timeinterval)
  {
    lasttime = millis();
    if (snakeMove())
    {
      matrix.fillScreen(matrix.Color333(0, 0, 0));
      for (int8_t i = 0; i < lenght; i++)
      {
        matrix.drawPixel(snake[i].x, snake[i].y, matrix.Color333(1, 1, 0));
      }
      matrix.drawPixel(apple.x, apple.y, matrix.Color333(1, 0, 0));
      if (lenght == 50)
      {
        for (int8_t i = 0; i < lenght; i++)
        {
          matrix.drawPixel(snake[i].x, snake[i].y, matrix.Color333(0, 1, 0));
        }
        delay(100);
        for (int8_t i = 0; i < lenght; i++)
        {
          matrix.drawPixel(snake[i].x, snake[i].y, matrix.Color333(1, 1, 0));
        }
        delay(100);
        for (int8_t i = 0; i < lenght; i++)
        {
          matrix.drawPixel(snake[i].x, snake[i].y, matrix.Color333(0, 1, 0));
        }
        delay(100);
        for (int8_t i = 0; i < 50; i++)
        {
          snake[i].set(0, 0);
        }
        newApple();
        lenght = 2;
        snake[0].set(15, 7);
        snake[1].set(14, 7);
        headdirection.set(1, 0);
        matrix.fillScreen(matrix.Color333(0, 0, 0));
      }
    }
    else
    {
      for (int8_t i = 0; i < lenght; i++)
      {
        matrix.drawPixel(snake[i].x, snake[i].y, matrix.Color333(1, 0, 0));
      }
      delay(1000);
      for (int8_t i = 0; i < 50; i++)
      {
        snake[i].set(0, 0);
      }
      newApple();
      lenght = 2;
      snake[0].set(15, 7);
      snake[1].set(14, 7);
      headdirection.set(1, 0);
      matrix.fillScreen(matrix.Color333(0, 0, 0));
    }
  }
}

int8_t temp;

void updateVel()
{
  if (digitalRead(playerleft) == HIGH)
  {
    temp = headdirection.x;
    headdirection.x = -headdirection.y;
    headdirection.y = temp;
  }
  else if (digitalRead(playerright) == HIGH)
  {
    temp = headdirection.y;
    headdirection.y = -headdirection.x;
    headdirection.x = temp;
  }
}

bool snakeMove()
{
  for (int8_t i = lenght; i > 0; i--)
  {
    snake[i].set(snake[i - 1]);
  }
  snake[0].set(snake[0].x + headdirection.x, snake[0].y + headdirection.y);
  if (snake[0].x == apple.x && snake[0].y == apple.y)
  {
    lenght++;
    newApple();
  }
  if (isSnake(snake[0]))
  {
    return false;
  }
  if (snake[0].x > 31 || snake[0].x < 0)
  {
    return false;
  }
  if (snake[0].y > 15 || snake[0].y < 0)
  {
    return false;
  }
  return true;
}

void newApple()
{
  apple.x = random(32);
  apple.y = random(16);
}

bool isSnake(cordinate cor)
{
  for (int8_t i = 1; i < lenght; i++)
  {
    if (snake[i].x == cor.x && snake[i].y == cor.y)
    {
      return true;
    }
  }
  return false;
}
