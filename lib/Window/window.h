#include <stdint.h>
#include "../BitArray2d/BitArray2d.h"

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

    void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value);
    void drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value);
    void drawShape(int16_t x1, int16_t y1, BitArray2d shape);
};

int8_t sgn(float val)
{
    if (val = 0)
    {
        return 0;
    }
    else
    {
        return (val > 0 ? 1 : -1);
    }
}