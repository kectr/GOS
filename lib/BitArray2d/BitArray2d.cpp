#include "BitArray2d.h"
#include <iostream>
using namespace std;

BitArray2d::BitArray2d()
{
}

void BitArray2d::takeDataFromMem()
{
    BitArray2d::data = new uint8_t[height * width_8];
    BitArray2d::fill();
}

void BitArray2d::initialize(uint16_t width, uint16_t height)
{
    BitArray2d::height = height;
    BitArray2d::width = width;
    BitArray2d::width_8 = (width + 7) / 8;
}

BitArray2d::BitArray2d(uint16_t width, uint16_t height, uint8_t *data)
{
    BitArray2d::initialize(height, width);
    BitArray2d::data = data;
    BitArray2d::dataTakenFromOut = true;
}

BitArray2d::BitArray2d(uint16_t width, uint16_t height)
{
    BitArray2d::initialize(width, height);
    BitArray2d::takeDataFromMem();
}

BitArray2d::~BitArray2d()
{
    if (!dataTakenFromOut)
    {
        delete[] data;
    }
}

uint8_t BitArray2d::read(uint16_t x, uint16_t y)
{
    return readBit(data[y * width_8 + x / 8], (x % 8));
}

void BitArray2d::write(uint16_t x, uint16_t y, uint8_t value)
{
    writeBit(data + y * width_8 + x / 8, (x % 8), value);
}

void BitArray2d::printout(uint8_t spaces)
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            printf("%d", read(i, j));
            for (int k = 0; k < spaces; k++)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void BitArray2d::printcout(uint8_t spaces)
{
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            cout << read(i, j);
            for (int k = 0; k < spaces; k++)
            {
                cout << " ";
            }
        }
        cout << "\n";
    }
}

void BitArray2d::fill(uint8_t value)
{
    for (uint16_t i = height * width_8 - 1;; i--)
    {
        data[i] = value;
        if (i == 0)
        {
            break;
        }
    }
}
