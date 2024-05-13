#ifndef window_h
#define window_h

#ifndef BitArray2d_h
#include "../BitArray2d/BitArray2d.h"
#endif

#ifndef sgn
#include "../sgn/sgn.h"
#endif

#include <string>

class window
{
private:
protected:
public:
    uint16_t width, height, x, y, z;
    BitArray2d content;

    window();
    ~window();
    void initialize(uint16_t _width, uint16_t _height, uint16_t _x, uint16_t _y, uint16_t _z);
    uint8_t isValidCordinate(int16_t x1, int16_t y1);
};

class drawableWindow : public window
{
private:
    /* data */
public:
    drawableWindow();
    ~drawableWindow();

    uint8_t drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value = 1);
    uint8_t drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value = 1);
    uint8_t drawShape(int16_t x1, int16_t y1, BitArray2d shape);
};

class textWindow : public drawableWindow
{
private:
    uint8_t *font = nullptr;
    uint8_t fontWidth = 0;
    uint8_t fontHeight = 0;

public:
    int16_t cursorX = 0, cursorY = 0;
    uint8_t strToFont(string str);

    textWindow(const uint8_t *font, uint8_t fontWidth, uint8_t fontHeight);
    ~textWindow();
};

int8_t sgn(float val);

float flabs(float val);

#endif