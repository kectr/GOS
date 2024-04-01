#include "window.h"
#include "stdio.h"

window::window()
{
}

window::~window()
{
}

void window::initialize(uint16_t _width, uint16_t _height, uint16_t _x, uint16_t _y, uint16_t _z)
{
    width = _width;
    height = _height;
    x = _x;
    y = _y;
    z = _z;
    content.initialize(width, height);
    content.takeDataFromMem();
}

void drawableWindow::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value)
{
    if (!(isValidCordinate(x1, y1) && isValidCordinate(x2, y2)))
    {
        return;
    }
    float x = x1, y = y1;
    float dx, dy;
    if (x1 == x2)
    {
        dx = 0;
        dy = sgn(y1 - y2);
    }
    else if (y1 == y2)
    {
        dy = 0;
        dx = sgn(x1 - x2);
    }
    else
    {
        dx = abs(float(x1 - x2) / float(y1 - y2));
        dy = 1 / dx;
    }
    if (dx < 1)
    {
        dy = sgn(y1 - y2);
        while (y != y2)
        {
            content.write(x, y, value);
            x += dx;
            y += dy;
        }
    }
    else
    {
        dx = sgn(x1 - x2);
        while (x != x2)
        {
            content.write(x, y, value);
            x += dx;
            y += dy;
        }
    }
    content.write(x2, y2, value);
}

void drawableWindow::drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value)
{
    if (!(isValidCordinate(x1, y1) && isValidCordinate(x2, y2)))
    {
        return;
    }
    drawLine(x1, y1, x1, y2, value);
    drawLine(x1, y1, x2, y1, value);
    drawLine(x2, y2, x1, y2, value);
    drawLine(x2, y2, x2, y1, value);
}

void drawableWindow::drawShape(int16_t x1, int16_t y1, BitArray2d shape)
{
    int16_t
        x,
        xStart,
        y,
        yStart,
        _x,
        _y,
        startX_shape = 0,
        startY_shape = 0,
        endX_shape = shape.width - 1,
        endY_shape = shape.heigt - 1;
    if (x1 < 0)
    {
        startX_shape = -x1;
        xStart = 0;
    }
    if (x1 >= width)
    {
        xStart = width - 1;
    }

    if (y1 < 0)
    {
        startY_shape = -y1;
        yStart = 0;
    }
    if (y1 >= height)
    {
        yStart = height - 1;
    }

    if (shape.width + x1 > width)
    {
        endX_shape = width - 1;
    }

    if (shape.heigt + y1 > height)
    {
        endY_shape = height - 1;
    }
    y = yStart;
    for (_y = startY_shape; _y <= endY_shape; _y++)
    {
        x = xStart;
        for (_x = startX_shape; _x <= endX_shape; _x++)
        {
            content.write(x, y, shape.read(_x, _y));
        }
    }
}

uint8_t window::isValidCordinate(int16_t x1, int16_t y1)
{
    if (x1 > width || y1 > height || x1 < 0 || y1 < 0)
    {
        return 0;
    }
    return 1;
}