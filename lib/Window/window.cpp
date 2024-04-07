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
        dy = abs(1 / dx) * sgn(y2 - y1);
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
    printf("a");
    if(x1>width||y1>height){
        return 0;
    }
    printf("b");
    int16_t
        x,
        y,
        shendx = shape.width-1,
        shendy = shape.height-1,
        shstx = 0,
        shsty = 0;
    printf("c");
    if (x1 < 0)
    {
        shstx = -x1;
    }
    printf("d");
    if (y1 < 0)
    {
        shsty = -y1;
    }
    printf("e");
    if (x1 + shape.width >= width)
    {
        shendx =width-x1-1;
    }
    printf("f");
    if (y1 + shape.height >= height)
    {
        shendy =height-y1-1;
    }
    printf("g");
    for(y = shsty;y<=shendy;y++){
        for(x = shstx;x<=shendx;x++){
            printf("%d-%d-%d-%d-%d\n",x,y,x+x1,y+y1,shape.read(x,y));
            content.write(x+x1,y+y1,shape.read(x,y));
            content.printout();
        }
    }
    content.printout();
    printf("h");
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