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

drawableWindow::drawableWindow()
{
}

drawableWindow::~drawableWindow()
{
}

uint8_t drawableWindow::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value)
{

    if (!(isValidCordinate(x1, y1) && isValidCordinate(x2, y2)))
    {
        return 0;
    }

    float x = x1, y = y1;
    float dx, dy;
    if (x1 == x2)
    {
        dx = 0;
        dy = sgn(y2 - y1);
    }
    else if (y1 == y2)
    {
        dy = 0;
        dx = sgn(x2 - x1);
    }
    else
    {
        dx = float(x2 - x1) / float(y2 - y1);
        dy = flabs(1 / dx) * sgn(y2 - y1);
    }
    if (-1 < dx && dx < 1)
    {

        dy = sgn(y2 - y1);
        while (y != y2)
        {
            // printf("%f-%f-%f-%f\n", x, y, dx, dy);
            content.write(x, y, value);
            x += dx;
            y += dy;
        }
    }
    else
    {
        dx = sgn(x2 - x1);
        while (x != x2)
        {
            // printf("%f-%f-%f-%f\n", x, y, dx, dy);
            content.write(x, y, value);
            x += dx;
            y += dy;
        }
    }
    content.write(x2, y2, value);
    return 1;
}

uint8_t drawableWindow::drawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t value)
{
    if (!(isValidCordinate(x1, y1) && isValidCordinate(x2, y2)))
    {
        return 0;
    }
    drawLine(x1, y1, x1, y2, value);
    drawLine(x1, y1, x2, y1, value);
    drawLine(x2, y2, x1, y2, value);
    drawLine(x2, y2, x2, y1, value);
    return 1;
}

uint8_t drawableWindow::drawShape(int16_t x1, int16_t y1, BitArray2d shape)
{
    if (x1 > width || y1 > height)
    {
        return 0;
    }
    int16_t
        x,
        y,
        shendx = shape.width - 1,
        shendy = shape.height - 1,
        shstx = 0,
        shsty = 0;
    if (x1 < 0)
    {
        shstx = -x1;
    }

    if (y1 < 0)
    {
        shsty = -y1;
    }
    if (x1 + shape.width >= width)
    {
        shendx = width - x1 - 1;
    }
    if (y1 + shape.height >= height)
    {
        shendy = height - y1 - 1;
    }
    for (y = shsty; y <= shendy; y++)
    {
        for (x = shstx; x <= shendx; x++)
        {
            content.write(x + x1, y + y1, shape.read(x, y));
        }
    }
    return 1;
}

uint8_t window::isValidCordinate(int16_t x1, int16_t y1)
{
    if (x1 > width || y1 > height || x1 < 0 || y1 < 0)
    {
        return 0;
    }
    return 1;
}

textWindow::textWindow(const uint8_t *font, uint8_t fontWidth, uint8_t fontHeight)
{
    textWindow::font = const_cast<uint8_t *>(font);
    textWindow::fontHeight = fontHeight;
    textWindow::fontWidth = fontWidth;
}

textWindow::~textWindow()
{
}

uint8_t textWindow::strToFont(string str)
{
    for (int16_t i = 0; i < str.length();)
    {
        BitArray2d nulchar(fontHeight, fontWidth, font);
        if (str[i] < ' ' || str[i] == 127)
        {
            switch (str[i])
            {
            case '\n':
                cursorX = 0;
                cursorY += fontHeight;
                i++;
                break;
            case 127:
                if (cursorX < fontWidth)
                {
                    cursorX = width;
                    if (cursorY < fontHeight)
                    {
                        break;
                    }
                    cursorY -= fontHeight;
                }
                else
                {
                    cursorX -= fontWidth;
                }
                drawShape(cursorX, cursorY, nulchar);
                i++;
                break;
            default:
                break;
            }
            continue;
        }
        else
        {
            if (cursorX + fontWidth - 1 < width)
            {
                BitArray2d character(fontWidth, fontHeight, font + fontWidth * (str[i]));
                drawShape(cursorX, cursorY, character);
                cursorX += fontWidth;
                i++;
            }
            else
            {
                cursorX = 0;
                if (cursorY + fontHeight < height)
                {
                    cursorY += fontHeight;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int8_t sgn(float val)
{
    if (0 == val)
    {
        return 0;
    }
    else
    {
        return (val > 0 ? 1 : -1);
    }
}

float flabs(float val)
{
    if (val < 0)
    {
        return -val;
    }
    else
    {
        return val;
    }
}